#pragma once

// (c) David Sykes 2013
// One more time, for the kids!

#include "Variable.h"
#include <vector>

namespace Script
{

class VariableStack
{
public:

	void				Push(const Variable&);
	const Variable	Pop();
	const Variable	GetHead() const;
	void				SetHead(const Variable&);
	Variable*		GetPointer(int offset){return &m_stack[m_stack.size()-offset];}
	void				Drop(int count){while (count-->0)Pop();}

private:
	std::vector<Variable>	m_stack;
};

}; // namespace Script

