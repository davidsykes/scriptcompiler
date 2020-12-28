#include "Interpreter.h"

// (c) David Sykes 2013
// One more time, for the kids!

#include <sstream>
#include <iostream>


namespace Script
{

Interpreter::Interpreter(const char* scriptData)
	: m_scriptData(scriptData)
	, m_currentPosition(scriptData)
{
}


Interpreter::~Interpreter(void)
{
}

/*

class IC:
	pushintvalue = 1
	pushparam = 2
	pushstring = 3
	pushvariable = 4
	popvariable = 5
	jfalse = 6
	jtrue = 7
	jall = 8
	add = 9
	subtract = 10
	multiply = 11
	devide = 12
	negate = 13
	logicalnot = 14
	lt = 15
	gt = 16
	lte = 17
	gte = 18
	equals = 19
	logicaland = 20
	logicalor = 21
	callfnroutine = 22
	dropstackvalue = 23
	endscript = 24
*/


bool Interpreter::Interpret()
{
	while (true)
	{
		int token = GetInteger();
		switch(token)
		{
			case 1:	//	pushintvalue
				{
					int v = GetInteger();
					std::cout << "Push int " << v << std::endl;
					m_stack.Push(v);
				}
				break;

			case 3:	//	pushstring
					m_stack.Push(Variable(GetString()));
				break;

			case 4:	//	Push variable
					m_stack.Push(GetVariable(GetString()));
					break;

			case 5:	// Pop variable
					SetVariable(GetString(), m_stack.Pop());
				break;

			case 6:	//	jfalse
				{
					int amountToJump = GetInteger();
					if (m_stack.Pop().Int() == 0)
						m_currentPosition += amountToJump;
					break;
				}

			case 7:	// jtrue = Jump if true
				{
					int amountToJump = GetInteger();
					if (m_stack.Pop().Int() != 0)
						m_currentPosition += amountToJump;
					break;
				}

			case 8:	// jall = Jump allways
				{
					int amountToJump = GetInteger();
					m_currentPosition += amountToJump;
					break;
				}

			case 9:	//	add
				{
					Variable v(m_stack.Pop());
					m_stack.SetHead(m_stack.GetHead() + v);
				}
				break;

			case 15:	//	lt
				{
					Variable v(m_stack.Pop());
					m_stack.SetHead(m_stack.GetHead() < v);
				}
				break;

			case 16:	//	gt
				{
					Variable v(m_stack.Pop());
					m_stack.SetHead(m_stack.GetHead() > v);
				}
				break;

			case 19:	//	equals
				{
					Variable v(m_stack.Pop());
					m_stack.SetHead(m_stack.GetHead() == v);
				}
				break;

			case 20:	//	logicaland
				{
					Variable v(m_stack.Pop());
					m_stack.SetHead(m_stack.GetHead().Int() && v.Int());
				}
				break;

			case 21:	//	logicalor
				{
					Variable v(m_stack.Pop());
					m_stack.SetHead(m_stack.GetHead().Int() || v.Int());
				}
				break;

			case 22: // callfnroutine
				{
					int parameterCount = GetInteger();
					const std::string fnroutine = GetString();
					Variable result;
					FnRoutine(fnroutine.c_str(), parameterCount, m_stack.GetPointer(parameterCount), result);
					m_stack.Drop(parameterCount);
					m_stack.Push(result);
				}
				break;

			case 23: // dropstackvalue
				std::cout << "dropstackvalue" << std::endl;
				m_stack.Pop();
				break;

			case 24:	// endscript
				return true;

			default:
				{
					std::stringstream ss;
					ss << "Unexpected token '" << token << "'";
					throw std::exception(ss.str().c_str());
				}
		}
	}
}


int Interpreter::GetInteger()
{
	int t = *((int*)m_currentPosition);
	m_currentPosition += sizeof(int);
	return t;
}

const char* Interpreter::GetString()
{
	const char *s = m_currentPosition;
	m_currentPosition = m_currentPosition + strlen(m_currentPosition) + 1;
	return s;
}

}; // namespace Script

