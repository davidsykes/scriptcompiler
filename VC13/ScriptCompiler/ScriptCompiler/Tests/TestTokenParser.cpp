

#include "..\TokenParser.h"
#include "TDDAssert.h"

class MockFileReader : public ILineFetcher
{
public:
	MockFileReader(){}
	MockFileReader(const char*script){}

private:
	virtual const char*	FetchLine()
	{
		return 0;
	}

};


void TestValidVariableChar()
{
	MockFileReader mr;
	TokenParser tp(mr);
		AssertTrue(ValidVariableChar('a'));
	AssertTrue(ValidVariableChar('z'));
	AssertTrue(ValidVariableChar('_'));
	AssertFalse(ValidVariableChar('?'));
}

void TestBasicTokens()
{
	MockFileReader mr("var _var1_23\n\n345   // comment\n1234{ }{} +=+-==/\n \r\n\t");
	TokenParser tp = TokenParser(mr);
	AssertEqual(tp.GetToken(), "var");
	AssertEqual(tp.GetToken(), "_var1_23");
	AssertEqual(tp.GetToken(), "345");
	AssertEqual(tp.GetToken(), "1234");
	AssertEqual(tp.GetToken(), "{");
	AssertEqual(tp.GetToken(), "}");
	AssertEqual(tp.GetToken(), "{");
	AssertEqual(tp.GetToken(), "}");
	AssertEqual(tp.GetToken(), "+");
	AssertEqual(tp.GetToken(), "=");
	AssertEqual(tp.GetToken(), "+");
	AssertEqual(tp.GetToken(), "-");
	AssertEqual(tp.GetToken(), "==");
	AssertEqual(tp.GetToken(), "/");
	AssertEqual(tp.GetToken(), "");

	AssertEqual(tp.GetLineNumber(), 7);
}

void TestMoreTokens()
{
	MockFileReader mr("&&&");
	TokenParser tp(mr);
	AssertEqual(tp.GetToken(), "&&");
	AssertEqual(tp.GetToken(), "&");
}

void TestOr()
{
	MockFileReader mr("| || |||");
	TokenParser tp(mr);
	AssertEqual(tp.GetToken(), "|");
	AssertEqual(tp.GetToken(), "||");
	AssertEqual(tp.GetToken(), "||");
	AssertEqual(tp.GetToken(), "|");
}

void TestReplaceToken()
{
	MockFileReader mr("one two three");
	TokenParser tp(mr);
	AssertEqual(tp.GetToken(), "one");
	AssertEqual(tp.GetToken(), "two");
	tp.ReplaceToken("four");
	AssertEqual(tp.GetToken(), "four");
	AssertEqual(tp.GetToken(), "three");
}

void TestScriptDefinitions()
{
	MockFileReader mr("scriptname(){}");
	TokenParser tp(mr);
	AssertEqual(tp.GetToken(), "scriptname");
	AssertEqual(tp.GetToken(), "(");
	AssertEqual(tp.GetToken(), ")");
	AssertEqual(tp.GetToken(), "{");
	AssertEqual(tp.GetToken(), "}");
}

void TestStrings()
{
	MockFileReader mr("bla\"string\"bla");
	TokenParser tp(mr);
	AssertEqual(tp.GetToken(), "bla");
	AssertEqual(tp.GetToken(), "\"string\"");
	AssertEqual(tp.GetToken(), "bla");
}

void TestTokenParser()
{
	TestValidVariableChar();
	TestBasicTokens();
	TestReplaceToken();
	TestMoreTokens();
	TestOr();
	TestScriptDefinitions();
	TestStrings();
}

