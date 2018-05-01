#!/usr/bin/env python

from Assert import AssertFailure
from TokenParser import ValidVariableChar
from ScriptEngine import Script

#--------------------------------------------------------------------------------------------------------
class MockScript(Script):

	def CompareScript(self, label, expected):
		script = self.GetScriptCode()
		count = len(script)
		if len(expected) < count:
			count = len(expected)
		for i in range(0,count):
			if script[i] != expected[i]:
				raise AssertFailure(''.join(['Script error in ', label, ' at position ', str(i), ' got ', str(script[i]), ' expected ', str(expected[i])]))
		if count < len(script):
			raise AssertFailure(''.join(['Got too much script in ', label]))
		if count < len(expected):
			raise AssertFailure(''.join(['Script: ', label, ' Only got ', str(len(script)), ' tokens out of ', str(len(expected))]))

#--------------------------------------------------------------------------------------------------------
class MockTokenParser:
	def __init__(self, script):
		self.tokens = script.split()
		self.nexttoken = 0
		self.tokenfetched = False

	def GetToken(self):
		self.tokenfetched = True
		if self.nexttoken < len(self.tokens):
			token = self.tokens[self.nexttoken]
			self.nexttoken = self.nexttoken + 1
		else:
			token = None
#      print 'GetToken', token
		return token

	def GetLineNumber(self):
		return 1

	def ValidVariableChar(self, ch):
		return ValidVariableChar(ch)

	def ReplaceToken(self, token):
		if token:
			self.nexttoken = self.nexttoken - 1

#--------------------------------------------------------------------------------------------------------
class MockVariables:
	def __init__(self, vars=None, enginefuncs=None):
		self.variables = {}
		self.functions = {}
		if vars:
			for var in vars:
				self.AddVariable(var)
		if enginefuncs:
			for f in enginefuncs:
				self.AddEngineFunction(f[0],f[1])

	def AddVariable(self, name):
		self.variables[name] = True

	def IsGlobalVariable(self, name):
		return name in self.variables

	def AddEngineFunction(self, name, parameterCount):
		self.functions[name] = parameterCount

	def IsFunction(self, name):
		return name in self.functions

	def GetScriptParameter(self, name):
		return None
