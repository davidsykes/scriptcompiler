#pragma once

#include <string>
#include <vector>
#include <map>

class Parameters
{
public:
	Parameters(const char *definitions, const char *const * const arguments, unsigned int startArgument);

	int Count()const{return m_parameters.size();}
	std::string operator[](int index)const{return m_parameters[index];}

	bool		GetFlag(char c){return m_flags[c];}
	std::string GetOption(char c)const;

	double		GetDouble(char c)const;

private:
	std::map<char,bool>			m_flags;
	std::map<char,std::string>	m_options;
	std::vector<std::string>	m_parameters;
};
