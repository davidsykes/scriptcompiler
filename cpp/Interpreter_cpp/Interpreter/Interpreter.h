#pragma once

// (c) David Sykes 2013
// One more time, for the kids!

#include "VariableStack.h"

namespace Script
{

class Interpreter
{
public:
	Interpreter(const char* scriptData);
	~Interpreter(void);

	bool	Interpret();

private:
	virtual void				SetVariable(const char* name, const Variable& var) = 0;
	virtual const Variable&	GetVariable(const char* name) = 0;
	virtual bool				FnRoutine(const char* name, int parameterCount, Variable* parameters, Variable& returnValue) = 0;

	int				GetInteger();
	const char*		GetString();

	VariableStack	m_stack;
	const char*		m_scriptData;
	const char*		m_currentPosition;
};


}; // namespace Script


