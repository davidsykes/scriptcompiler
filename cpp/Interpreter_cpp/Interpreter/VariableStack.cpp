#include "VariableStack.h"
#include "InterpreterException.h"

// (c) David Sykes 2013
// One more time, for the kids!

namespace Script
{

	void VariableStack::Push(const Variable& v)
	{
		m_stack.push_back(v);
	}

	const Variable	VariableStack::Pop()
	{
		if (m_stack.size() > 0)
		{
			Variable pop = m_stack.back();
			m_stack.pop_back();
			return pop;
		}
		else
			throw InterpreterException("Stack underflow");
	}

	void VariableStack::SetHead(const Variable& v)
	{
		if (m_stack.size() == 0)
			throw InterpreterException("Empty stack error");
		m_stack.back() = v;
	}

	const Variable	VariableStack::GetHead() const
	{
		if (m_stack.size() > 0)
		{
			return m_stack.back();
		}
		throw InterpreterException("Empty stack error");
	}

}; // namespace Script
