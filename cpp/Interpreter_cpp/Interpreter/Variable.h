#pragma once

// (c) David Sykes 2013
// One more time, for the kids!

#include <string>

namespace Script
{

class Variable
{
public:
	Variable() : m_int(0){}
	Variable(int v) : m_variableIsInteger(true),m_int(v){}
	Variable(const std::string& v):m_variableIsInteger(false),m_int(0),m_string(v){}

	int						Int()const{return m_int;}
	const std::string		String()const{return m_string;}

	const Variable			operator +(const Variable& v)const;
	const Variable			operator +(int v)const;
	const Variable			operator +(const char *)const;
	const Variable			operator +(const std::string& v)const;

	bool						operator ==(const Variable& v)const;
	bool						operator <(const Variable& v)const;
	bool						operator <=(const Variable& v)const{return (*this <v)||(*this == v);}
	bool						operator >(const Variable& v)const{return !((*this <v)||(*this == v));}
	bool						operator >=(const Variable& v)const{return !(*this <v);}

private:
	Variable(int i, const std::string& s):m_int(i),m_string(s){}

	bool			m_variableIsInteger;
	int			m_int;
	std::string	m_string;
};


}; // namespace Script
