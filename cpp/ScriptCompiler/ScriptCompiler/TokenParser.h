//(c) David Sykes 2014
// One more time, for the kids!

#pragma once
#include "ILineFetcher.h"
#include <string>


inline bool ValidVariableChar(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

class TokenParser
{
public:
	TokenParser(ILineFetcher& lineFetcher);
	const std::string&	GetToken();
	void				ReplaceToken(const std::string& token);
	int					GetLineNumber()const{ return 0; }

private:
	ILineFetcher&	m_lineFetcher;
	const char*		m_currentLine;
};