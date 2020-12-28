// (c) David Sykes 2014
// One more time, for the kids!

#include "OperatorStack.h"

#if 0
	def __init__(self) :
	self.stack = []

	def IsEmpty(self) :
	if self.stack :
		return False
		return True

		def GetPrecedence(self) :
	if self.stack :
		return self.stack[-1].precedence
		return 0

		def Push(self, operator) :
		self.stack.append(operator)

		def Pop(self) :
		return self.stack.pop()
};

#endif

int OperatorStack::GetPrecedence() const
{
	if (m_stack.empty())
		return 0;
	return m_stack.top().precedence;
}
