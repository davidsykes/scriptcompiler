#pragma once

#include "../IVariableEngine.h"
#include "../Script.h"
#include "../ITokenParser.h"
#include "../PCodeItem.h"

//--------------------------------------------------------------------------------------------------------

class MockScript : public Script
{
public:
	MockScript(const std::string& name) :Script(name){}

	void CompareScript(const std::string& label, const std::vector<PCodeItem>& expectedData) const;
};


//--------------------------------------------------------------------------------------------------------
class MockTokenParser : public ITokenParser
{
public:
	MockTokenParser(const std::string& script);

#if 0
	def GetToken(self) :
	self.tokenfetched = True
	if self.nexttoken < len(self.tokens) :
		token = self.tokens[self.nexttoken]
		self.nexttoken = self.nexttoken + 1
	else :
	token = None
#      print 'GetToken', token
	return token

	def GetLineNumber(self) :
	return 1

	def ValidVariableChar(self, ch) :
	return ValidVariableChar(ch)

	def ReplaceToken(self, token) :
	if token :
		self.nexttoken = self.nexttoken - 1

#endif
};

//--------------------------------------------------------------------------------------------------------


class MockVariables : public IVariableEngine
{
public:
	MockVariables(){}
	MockVariables(const std::vector<std::string>& variables);

#if 0
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
#endif
		};