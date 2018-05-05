#pragma once


class ITokenParser
{
public:
	virtual ~ITokenParser() = 0{}

	virtual const std::string	GetToken() = 0;
	virtual int					GetLineNumber() = 0;
};