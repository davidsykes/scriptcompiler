// (c) David Sykes 2014
// One more time, for the kids!

#include "IVariableEngine.h"
#include <map>
#include "Operator.h"
#include "ITokenParser.h"
#include "Script.h"
#include "OperatorStack.h"


class ExpressionParser
{
public:
						ExpressionParser(IVariableEngine& variables);

	const std::string	ParseExpression(ITokenParser& tokenparser, Script& script);
	bool				IsExpressionTerminator(const std::string& token) const;
	const Operator*		GetUnaryOperator(const std::string& token) const;

private:
	const std::string	ParseExpression2(ITokenParser& tokenparser, Script& script, OperatorStack& operatorstack);

	std::map<std::string, Operator>	m_unaryoperators;
	std::map<std::string, Operator>	m_operators;
	IVariableEngine&				m_variables;

#if 0

		def ParseEngineFunction(self, fname, tokenparser, script, operatorstack = None) :

	def IsExpressionTerminator(self, token) :

		def GetOperator(self, token) :
#endif

};

