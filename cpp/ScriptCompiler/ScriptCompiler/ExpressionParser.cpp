// (c) David Sykes 2014
// One more time, for the kids!

#include "ExpressionParser.h"
#include <string>
#include "Interpreter.h"
#include "OperatorStack.h"


ExpressionParser::ExpressionParser(IVariableEngine& variables) : m_variables(variables)
{
	m_unaryoperators["-"] = Operator(negate, 6);
	m_unaryoperators["!"] = Operator(logicalnot, 6);

		//	http://en.cppreference.com/w/cpp/language/operator_precedence
	m_operators["-"] = Operator(add, 4);
	m_operators["+"] = Operator(add, 4);
	m_operators["*"] = Operator(multiply, 5);
	m_operators["/"] = Operator(devide, 5);
	m_operators["<"] = Operator(lt, 8);
	m_operators[">"] = Operator(gt, 8);
	m_operators["<="] = Operator(lte, 8);
	m_operators[">="] = Operator(gte, 8);
	m_operators["=="] = Operator(equals, 9);
	m_operators["&&"] = Operator(logicaland, 13);
	m_operators["and"] = Operator(logicaland, 13);
	m_operators["||"] = Operator(logicalor, 14);
	m_operators["or"] = Operator(logicalor, 14);
}

const std::string ExpressionParser::ParseExpression(ITokenParser& tokenparser, Script& script)
{
	OperatorStack operatorstack;
	const std::string token = ParseExpression2(tokenparser, script, operatorstack);
	while (!operatorstack.IsEmpty())
		script.AddTokenInt(operatorstack.Pop().scriptCommand);
	return token;
}


const std::string ExpressionParser::ParseExpression2(ITokenParser& tokenparser, Script& script, OperatorStack& operatorstack)
{
	while (true)
	{
		// Expecting some kind of value here
		std::string token = tokenparser.GetToken();
		if (IsExpressionTerminator(token))
			return token;

		const Operator* unaryoperator = GetUnaryOperator(token);
		if (unaryoperator)
		{
			operatorstack.Push(*unaryoperator);
			token = tokenparser.GetToken();
		}

		if (token.empty())
			throw CompileError("10: Unexpected end of script", tokenparser.GetLineNumber());

		if (token == "(")
		{
			// Recursive expression
			token = self.ParseExpression2(tokenparser, script, operatorstack);
			if (token != ")")
				throw CompileError(''.join(["Expected ')' not '", token, "'"]), tokenparser.GetLineNumber());
		}
		else
		{
			if (token[0] == '"')
			{
				script.AddTokenInt(IC.pushstring)
					script.AddTokenString(token)
					elif self.variables.IsGlobalVariable(token) :
					script.AddTokenInt(IC.pushvariable)
					script.AddTokenString(token)
					elif self.variables.IsFunction(token) :
					self.ParseEngineFunction(token, tokenparser, script, operatorstack)
					elif self.variables.GetScriptParameter(token) != None :
					script.AddTokenInt(pushparam)
					script.AddTokenInt(self.variables.GetScriptParameter(token))
			}
			else:
			{
				try
				{
					value = int(token)
						script.AddTokenInt(pushintvalue)
						script.AddTokenInt(value)
				}
				except ValueError :
				{
					raise CompileError(''.join(["08: '", token, "' not recognised as value or variable"]), tokenparser.GetLineNumber())
				}
			}

			// Now expecting an operator or end of expression
			token = tokenparser.GetToken();
			if (IsExpressionTerminator(token))
				return token;

			Operator op = GetOperator(token);
			if (op)
			{
				while (op.precedence <= operatorstack.GetPrecedence())
				{
					script.AddTokenInt(operatorstack.Pop().scriptcommand);
					operatorstack.Push(op);
				}
			}
			else:
			raise CompileError(''.join(['03: Unrecognised token "', token, '" in expression']), tokenparser.GetLineNumber())
		}
	}

#if 0

	def ParseEngineFunction(self, fname, tokenparser, script, operatorstack=None):
		if operatorstack == None:
			operatorstack = OperatorStack()
		if tokenparser.GetToken() != '(':
			raise CompileError('09: Engine function parameter list expected', tokenparser.GetLineNumber())

		# Zero or more parameters
		expressionend= ","
		parameterCount = 0
		while expressionend == ",":
			expressionend = self.ParseExpression(tokenparser, script)
			parameterCount = parameterCount + 1
		if expressionend != ')':
			raise CompileError('07: Engine function parameter list should end in ")"', tokenparser.GetLineNumber())
		script.AddTokenInt(callfnroutine);
		script.AddTokenInt(parameterCount)
		script.AddTokenString(fname);
#endif

		bool ExpressionParser::IsExpressionTerminator(const std::string& token) const
		{
			static std::string terminators = ";,)";
			return ((token.size() <= 1) && ((token.size() == 0) || (terminators.find_first_of(token[0]) != std::string::npos)));
		}

		const Operator* ExpressionParser::GetUnaryOperator(const std::string& token) const
		{
			std::map<std::string, Operator>::const_iterator it = m_unaryoperators.find(token);
			if (it == m_unaryoperators.end())
				return nullptr;

			return &it->second;
		}
#if 0
				def GetOperator(self, token) :
		try:
			return self.operators[token]
		except KeyError:
			return None
#endif