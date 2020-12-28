#include "TDDAssert.h"

#include "../ExpressionParser.h"
#include "MockObjects.h"
#include "../Interpreter.h"
#include <array>

void TestExpressionTerminators()
{
	MockVariables mv;
	ExpressionParser ep(mv);

	AssertTrue(ep.IsExpressionTerminator(';'));
	AssertTrue(ep.IsExpressionTerminator(')'));
	AssertTrue(ep.IsExpressionTerminator(','));
	AssertTrue(ep.IsExpressionTerminator(0));
}

void TestUnaryOperators()
{
	MockVariables mv;
	ExpressionParser ep(mv);
	AssertTrue(ep.GetUnaryOperator("+") == nullptr);
	AssertFalse(ep.GetUnaryOperator("-") == nullptr);
	AssertFalse(ep.GetUnaryOperator("!") == nullptr);
	AssertFalse(ep.GetUnaryOperator("/") == nullptr);
}

void TestExpressionParserNumeric()
{
	MockVariables mv;
	ExpressionParser ep(mv);
	MockScript script("name");
	ep.ParseExpression(MockTokenParser("2 + 3 * 4"), script);

	script.CompareScript("texprn", { PCodeItem(pushintvalue),
		PCodeItem(2),
		PCodeItem(pushintvalue),
		PCodeItem(3),
		PCodeItem(pushintvalue),
		PCodeItem(4),
		PCodeItem(multiply),
		PCodeItem(add) });
}

void TestExpressionParserVariables()
{
	MockVariables mv({ "var1", "var2" });
	ExpressionParser ep(mv);
	MockScript script("name");
	ep.ParseExpression(MockTokenParser("var1 / var2"), script);
	script.CompareScript("texprv", { PCodeItem(pushvariable),
		PCodeItem("var1"),
		PCodeItem(pushvariable),
		PCodeItem("var2"),
		PCodeItem(devide) });
}

void TestExpressionParserComplex()
{
	MockVariables variables({ "var1" });
	ExpressionParser ep(variables);
	MockScript script("name");
	ep.ParseExpression(MockTokenParser("- 2 * ( var1 == 4 )"), script);
	script.CompareScript("texprcx", { pushintvalue,
		2,
		negate,
		pushvariable,
		'var1',
		pushintvalue,
		4,
		equals,
		multiply });
}

void TestExpressionParser()
{
	TestExpressionTerminators();
	TestUnaryOperators();
	TestExpressionParserNumeric();
	TestExpressionParserVariables();
	TestExpressionParserComplex();
}
