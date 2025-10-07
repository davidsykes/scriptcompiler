#pragma once
// (c) David Sykes 2014
// One more time, for the kids!

#include "Interpreter.h"
#include <string>

// A PCodeItem is an item or partially compiled data
// It can either be a string, or an integer, and allows
// the different types to be held in an array

class PCodeItem
{
public:
	PCodeItem(IC ic) : m_intValue(ic){}
	PCodeItem(int i) : m_intValue(i){}
	PCodeItem(const std::string& s) : m_stringValue(s) {}

private:
	//bool	m_isString;
	int			m_intValue;
	std::string	m_stringValue;
};

