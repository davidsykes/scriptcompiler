#pragma once

// (c) David Sykes 2013
// One more time, for the kids!

#include "Interpreter.h"
#include "Variable.h"
#include <map>

class MockInterpreter : public Script::Interpreter
{
public:
	MockInterpreter(const char*data) : Script::Interpreter(data) {}

private:
	virtual void							SetVariable(const char* name, const Script::Variable& var) ;
	virtual const Script::Variable&	GetVariable(const char* name);
	virtual bool							FnRoutine(const char* name, int parameterCount, Script::Variable* parameters, Script::Variable& returnValue);


	std::map<std::string, Script::Variable>	m_variables;
};



