#pragma once
// (c) David Sykes 2014
// One more time, for the kids!

#include "Operator.h"
#include <stack>

class OperatorStack
{
public:
	bool			IsEmpty() const{ return m_stack.empty(); }
	void			Push(const Operator& op){ m_stack.push(op); }
	const Operator	Pop(){ const Operator op(m_stack.top()); m_stack.pop(); return op; }
	int				GetPrecedence() const;

private:
	std::stack<Operator>	m_stack;
};


