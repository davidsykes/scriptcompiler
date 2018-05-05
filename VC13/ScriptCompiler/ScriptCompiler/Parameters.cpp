#include "Parameters.h"
#include <map>
#include <sstream>



Parameters::Parameters(const char *definitions, const char * const * const arguments, unsigned int startArgument)
{
	// Process the definitions map
	std::map<char, bool> flagSpecs;

	if (definitions)
	{
		while (*definitions)
		{
			if (isalpha(*definitions))
			{
				if (flagSpecs.find(*definitions) == flagSpecs.end())
				{
					if (definitions[1] == ':')
						flagSpecs[*definitions++] = true;
					else
						flagSpecs[*definitions] = false;
				}
				else
					throw std::exception("Repeated parameter");
			}
			else
				throw std::exception("Invalid parameter definitions");

			++definitions;
		}
	}

	// Are there actually any arguments
	if (!arguments)
		return;

	typedef enum { NORMAL, OPTION_PARAMETER } ProcessingState;
	ProcessingState state = NORMAL;
	char option;

	for (int arg = startArgument ; arguments[arg] ; arg++)
	{
		if (state == NORMAL)
		{
			if (arguments[arg][0] == '-')
			{
				// An option of some sort
				if (strlen(arguments[arg]) > 2)
					throw std::exception("Option too long");
				option = arguments[arg][1];
				if (flagSpecs.find(option) == flagSpecs.end())
				{
					std::stringstream ss;
					ss << "Undefined option value '" << arguments[arg] << "'";
					throw std::exception( ss.str().c_str());
				}
				if (flagSpecs[option])
					state = OPTION_PARAMETER;
				else
					m_flags[option] = true;
			}
			else
				m_parameters.push_back(arguments[arg]);
		}
		else
		{
			// An option value

			std::map<char,std::string>::iterator it = m_options.find(option);
			if ( (it != m_options.end()) && (it->second != arguments[arg]))
			{
				std::stringstream ss;
				ss << "Repeated option value '" << arguments[arg] << "' given different values";
				throw std::exception( ss.str().c_str());
			}


			m_options[option] = arguments[arg];
			state = NORMAL;
		}
	}
	if (state != NORMAL)
		throw std::exception("Missing option value");
}

std::string Parameters::GetOption(char c)const
{
	std::map<char,std::string>::const_iterator it = m_options.find(c);
	if (it == m_options.end())
		return "";
	return it->second.c_str();
}


double Parameters::GetDouble(char c)const
{
	return atof(GetOption(c).c_str());
}
