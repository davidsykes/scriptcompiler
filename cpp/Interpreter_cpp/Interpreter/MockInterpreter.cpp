
// (c) David Sykes 2013
// One more time, for the kids!

#include "MockInterpreter.h"

#include <iostream>

void MockInterpreter::SetVariable(const char* name, const Script::Variable& var)
{
	std::cout << "Set variable " << name << " to " << var.Int() << "/'" << var.String() << "'" << std::endl;
	m_variables[name] = var;
}

const Script::Variable& MockInterpreter::GetVariable(const char* name)
{
	const Script::Variable& var = m_variables[name];
	std::cout << "Get variable " << name << " =  " <<  var.Int() << "/'" << var.String() << "'" << std::endl;
	return var;
}

bool MockInterpreter::FnRoutine(const char* name, int parameterCount, Script::Variable* parameters, Script::Variable& returnValue)
{
	std::cout << "Fn routine " << name << "(";
	for (int p = 0 ; p < parameterCount ; ++p)
		std::cout << parameters[p].Int() << "/'" << parameters[p].String() << "',";
	std::cout << ")" << std::endl;
	return true;
}
