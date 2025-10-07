#include "Variable.h"

// (c) David Sykes 2013
// One more time, for the kids!

namespace Script
{

	const Variable Variable::operator +(int v) const
	{
		return Variable(m_int + v);
	}

	const Variable Variable::operator +(const char * v) const
	{
		return Variable(m_string + v);
	}

	const Variable Variable::operator +(const Variable& v) const
	{
		return Variable(m_int + v.Int(), m_string + v.String());
	}

	bool Variable::operator ==(const Variable& v)const
	{
		if (m_variableIsInteger)
			return m_int == v.m_int;
		return m_string == v.m_string;
	}

	bool Variable::operator <(const Variable& v)const
	{
		if (m_variableIsInteger)
			return m_int < v.m_int;
		return m_string < v.m_string;
	}

}; // namespace Script


