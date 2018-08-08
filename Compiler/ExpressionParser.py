#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

from Interpreter import IC
from CompileError import CompileError
from OperatorStack import OperatorStack

class Operator:
	def __init__(self, command, precedence):
		self.scriptcommand = command
		self.precedence = precedence

class ExpressionParser:
	def __init__(self, variables):
		self.variables = variables

		self.unaryoperators = {}
		self.unaryoperators['-'] = Operator(IC.negate, 6)
		self.unaryoperators['!'] = Operator(IC.logicalnot, 6)

		#http://en.cppreference.com/w/cpp/language/operator_precedence
		self.operators = {}
		self.operators ['-']= Operator(IC.subtract, 4)
		self.operators ['+']= Operator(IC.add, 4)
		self.operators ['*']= Operator(IC.multiply, 5)
		self.operators ['/']= Operator(IC.devide, 5)
		self.operators ['<']= Operator(IC.lt, 8)
		self.operators ['>']= Operator(IC.gt, 8)
		self.operators ['<=']= Operator(IC.lte, 8)
		self.operators ['>=']= Operator(IC.gte, 8)
		self.operators ['==']= Operator(IC.equals, 9)
		self.operators ['&&']= Operator(IC.logicaland, 13)
		self.operators ['and']= Operator(IC.logicaland, 13)
		self.operators ['||']= Operator(IC.logicalor, 14)
		self.operators ['or']= Operator(IC.logicalor, 14)

	def ParseExpression(self, tokenparser, script):
		operatorstack = OperatorStack()
		token = self.ParseExpression2(tokenparser, script, operatorstack)
		while not operatorstack.IsEmpty():
			script.AddTokenInt(operatorstack.Pop().scriptcommand)
		return token

	def ParseExpression2(self, tokenparser, script, operatorstack):
		while True:
			# Expecting some kind of value here
			token = tokenparser.GetToken()
			if self.IsExpressionTerminator(token):
				return token

			unaryoperator = self.GetUnaryOperator(token)
			if unaryoperator:
				operatorstack.Push(unaryoperator)
				token = tokenparser.GetToken()

			if not token or len(token) == 0:
				raise CompileError('10: Unexpected end of script', tokenparser.GetLineNumber())
			if token == '(':
				# Recursive expression
				token = self.ParseExpression2(tokenparser, script, operatorstack)
				if token != ')':
					raise CompileError(''.join(["Expected ')' not '", token, "'"]), tokenparser.GetLineNumber())
			else:
				if token[0] == '"':
					script.AddTokenInt(IC.pushstring)
					script.AddTokenString(token[1:-1])
				elif self.variables.IsGlobalVariable(token):
					script.AddTokenInt(IC.pushglobalvariable)
					script.AddTokenString(token)
				elif self.variables.IsLocalVariable(token):
					script.AddTokenInt(IC.pushlocalvariable)
					script.AddTokenString(token)
				elif self.variables.IsFunction(token):
					self.ParseEngineFunction(token, tokenparser, script, operatorstack)
				elif self.variables.GetScriptParameter(token) != None:
					script.AddTokenInt(IC.pushparam)
					script.AddTokenInt(self.variables.GetScriptParameter(token))
				else:
					try:
						value = int(token)
						script.AddTokenInt(IC.pushintvalue)
						script.AddTokenInt(value)
					except ValueError:
						raise CompileError(''.join(["08: '",token,"' not recognised as value or variable"]), tokenparser.GetLineNumber())

			# Now expecting an operator or end of expression
			token = tokenparser.GetToken()
			if self.IsExpressionTerminator(token):
				return token

			operator = self.GetOperator(token)
			if operator:
				while operator.precedence <= operatorstack.GetPrecedence():
					script.AddTokenInt(operatorstack.Pop().scriptcommand)
				operatorstack.Push(operator)
			else:
				raise CompileError(''.join(['03: Unrecognised token "', token, '" in expression']), tokenparser.GetLineNumber())

	def ParseEngineFunction(self, fname, tokenparser, script, operatorstack=None):
		if operatorstack == None:
			operatorstack = OperatorStack()
		if tokenparser.GetToken() != '(':
			raise CompileError('09: Engine function parameter list expected', tokenparser.GetLineNumber())

		# Zero or more parameters
		parameterCount = 0

		firstParameterToken = tokenparser.GetToken()
		if firstParameterToken != ')':
			tokenparser.ReplaceToken(firstParameterToken)

			expressionend= ","
			while expressionend == ",":
				expressionend = self.ParseExpression(tokenparser, script)
				parameterCount = parameterCount + 1
			if expressionend != ')':
				raise CompileError('07: Engine function parameter list should end in ")"', tokenparser.GetLineNumber())
		script.AddTokenInt(IC.callfnroutine)
		script.AddTokenInt(parameterCount)
		script.AddTokenString(fname)

	def IsExpressionTerminator(self, token):
		return token == None or token in [';',')',',']

	def GetUnaryOperator(self, token):
		try:
			return self.unaryoperators[token]
		except KeyError:
			return None

	def GetOperator(self, token):
		try:
			return self.operators[token]
		except KeyError:
			return None
