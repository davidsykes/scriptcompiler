#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

from ExpressionParser import ExpressionParser
from CompileError import CompileError
from Interpreter import IC


class CompileEngine:
	def __init__(self, tokenparser, variables, scripts):
		self.tokenparser = tokenparser
		self.variables = variables
		self.scripts = scripts
		self.expressionparser = ExpressionParser(variables)

	def Process(self):
		token = self.tokenparser.GetToken()
		while token:
			if token == 'struct':
				# struct ob_menu name ;
				self.RequireNextToken('ob_menu', 'struct')
				name = self.tokenparser.GetToken()
				self.RequireNextToken(';', 'ob_menu name')
				self.variables.AddObMenuVariable(name)
			elif token == 'Global':
				# Global name ;
				name = self.tokenparser.GetToken()
				self.RequireNextToken(';', 'Global name')
				self.variables.AddGlobalVariable(name)
			elif token == 'const':
				# const name = intvalue ;
				name = self.tokenparser.GetToken()
				self.RequireNextToken('=', 'const definition')
				value = self.tokenparser.GetToken()
				try:
					ivalue = int(value)
				except ValueError:
					raise CompileError(''.join(["Invalid integer '", value, "'"]), self.tokenparser.GetLineNumber())
				self.variables.AddConstDefinition(name, ivalue)
				self.RequireNextToken(';', 'const definition')
			elif self.tokenparser.ValidVariableChar(token):
				#----- Script definition ---------
				self.ProcessScriptDefinition(token)
				self.variables.ClearScriptLocalVariables()
			else:
				raise CompileError(''.join(["01: Unrecognised token '", token, "'"]), self.tokenparser.GetLineNumber())

			token = self.tokenparser.GetToken()

	def ProcessScriptDefinition(self, scriptname):
			script = self.scripts.CreateScript(scriptname)
			# We may have parameters
			self.variables.ClearScriptParameters()
			self.RequireNextToken('(', 'script definition')
			token = self.tokenparser.GetToken()
			while token != ')':
				if self.tokenparser.ValidVariableChar(token):
					if self.variables.IsGlobalVariable(token):
						raise CompileError(''.join(["06: Script parameter ', token, ' hides global variable"]), self.tokenparser.GetLineNumber())
					self.variables.AddScriptParameter(token)
				else:
					raise CompileError(''.join(["Invalid script paramter '", token, "'"]) , self.tokenparser.GetLineNumber())

				token = self.tokenparser.GetToken()
				if token not in [',', ')']:
					raise CompileError("expected ',' or ')'", self.tokenparser.GetLineNumber())

			self.CompileSingleExecutionBlock(script)
			script.AddTokenInt(IC.endscript)
			self.variables.ClearScriptParameters()

	def RequireNextToken(self, token, whatcamebefore):
		next = self.tokenparser.GetToken()
		if next != token:
				raise CompileError(''.join(["Expected '", token, "' instead of '", next, "' after '", whatcamebefore, "'"]), self.tokenparser.GetLineNumber())

	def CompileSingleExecutionBlock(self, script):
		token = self.tokenparser.GetToken()

		if token == None:
			raise CompileError('10: Unexpected end of script', self.tokenparser.GetLineNumber())

		if token == '{':
			# Multiple execution blocks wrapped in { }
			while True:
				token = self.tokenparser.GetToken()
				if token == '}':
					return
				self.tokenparser.ReplaceToken(token)
				self.CompileSingleExecutionBlock(script)

		#---- If ----------
		elif token == 'if':
			self.ParseIfStatement(script)
		#---- Do ----------
		elif token == 'do':
			self.ParseDoStatement(script)
		#---- Pause -------
		elif token == 'pause':
			self.ParsePauseStatement(script)
		#---- local -------
		elif token == 'local':
			self.ParseLocalStatement(script)
		elif self.variables.IsGlobalVariable(token):
			#----- Variable assignment
			self.RequireNextToken('=', ''.join(['Assignment to variable ', token]))
			if self.expressionparser.ParseExpression(self.tokenparser, script) != ';':
				raise CompileError(''.join(["Expression should be terminated by ';', found '", token, "'"]), self.tokenparser.GetLineNumber())
			script.AddTokenInt(IC.popglobalvariable)
			script.AddTokenString(token)
		elif self.variables.IsLocalVariable(token):
			#----- Variable assignment
			self.RequireNextToken('=', ''.join(['Assignment to variable ', token]))
			if self.expressionparser.ParseExpression(self.tokenparser, script) != ';':
				raise CompileError(''.join(["Expression should be terminated by ';', found '", token, "'"]), self.tokenparser.GetLineNumber())
			script.AddTokenInt(IC.poplocalvariable)
			script.AddTokenString(token)
		elif self.variables.IsFunction(token):
			self.ParseEngineFunction(token, script)
		else:
			raise CompileError(''.join(["02: Unrecognised token '", token, "'"]), self.tokenparser.GetLineNumber())


	def ParseIfStatement(self, script):
			# We have an if statement
		self.RequireNextToken('(', 'if')
		expressionend = self.expressionparser.ParseExpression(self.tokenparser, script)
		if expressionend != ')':
			raise CompileError(''.join(["04: Unexpected token '", str(expressionend), "' at end of expression"]), self.tokenparser.GetLineNumber())

		# if expression has been evaluated. Jump to any 'else' part if expression is false
		script.AddTokenInt(IC.jne)
		# Add a dummy offset to be updated later
		jneindex = script.GetEndIndex2()
		script.AddTokenInt(0)
		jneoffset = script.GetEndPC()

		# Parse the true section
		self.CompileSingleExecutionBlock(script)

		# If there is an else then we need to jump past it
		token = self.tokenparser.GetToken()
		if token in ['else', 'elseif']:
			script.AddTokenInt(IC.jall)
			elsejumpindex = script.GetEndIndex2()
			script.AddTokenInt(0)
			elsejumpoffset = script.GetEndPC()
			# The jne jump jumps here
			script.SetToken(jneindex, script.GetEndPC() - jneoffset)
			if token == 'elseif':
				#Parse a fresh if statemement, and make earlier if jump to the end of here
				self.ParseIfStatement(script)
			else:
				# Do the else stuff
				self.CompileSingleExecutionBlock(script)
			# The jall jumps here
			script.SetToken(elsejumpindex, script.GetEndPC() - elsejumpoffset)
		else:
			self.tokenparser.ReplaceToken(token)
			# The jall jump jumps here
			script.SetToken(jneindex, script.GetEndPC() - jneoffset)

	def ParseDoStatement(self, script):
		# do
		dopositionpc = script.GetEndPC()
		self.CompileSingleExecutionBlock(script)
		# while
		self.RequireNextToken('while', 'do')
		self.RequireNextToken('(', 'do')
		# expression
		expressionend = self.expressionparser.ParseExpression(self.tokenparser, script)
		if expressionend != ')':
			raise CompileError(''.join(["05: Unexpected token '", str(expressionend), "' at end of expression"]), self.tokenparser.GetLineNumber())
		self.RequireNextToken(';', 'do')
		# if expression is true jump back to start of do
		script.AddTokenInt(IC.jtrue)
		script.AddTokenInt(dopositionpc - script.GetEndPC())

	def ParsePauseStatement(self, script):
		# pause
		script.AddTokenInt(IC.pause)
		self.RequireNextToken(';', 'pause')

	def ParseLocalStatement(self, script):
		localvariablename = self.tokenparser.GetToken()
		self.variables.AddScriptLocalVariable(localvariablename)
		self.RequireNextToken(';', 'local')

	def ParseEngineFunction(self, fnName, script):
		fnpositionpc = script.GetEndPC()
		self.expressionparser.ParseEngineFunction(fnName, self.tokenparser, script)
		self.RequireNextToken(';', 'engine function')
		script.AddTokenInt(IC.dropskippausenonzero)
		jumppositionpc = script.GetEndPC()
		script.AddTokenInt(fnpositionpc - jumppositionpc)
