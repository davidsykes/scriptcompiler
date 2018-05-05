
#include "..\ScriptEngine.h"
#include "..\Script.h"
#include "TDDAssert.h"


void TestAddStuffToScript()
{
	ScriptEngine se;
	Script& script = se.CreateScript("test");
	script.AddTokenInt(1);
	AssertEqual(1, script.GetEndIndex());
	AssertEqual(4, script.GetEndPC());
	script.AddTokenInt(2);
	AssertEqual(2, script.GetEndIndex());
	AssertEqual(8, script.GetEndPC());
	script.AddTokenString("fried");
	AssertEqual(3, script.GetEndIndex());
	AssertEqual(14, script.GetEndPC());
}

void TestSetToken()
{
	ScriptEngine se;
	Script& script = se.CreateScript("test");
	script.AddTokenInt(1);
	script.AddTokenInt(2);
	script.AddTokenInt(3);
	AssertEqual(script.GetScriptCode(), std::vector<__int32>{ 1, 2, 3 });
	script.SetToken(1, 4);
	AssertEqual(script.GetScriptCode(), std::vector<__int32>{1, 4, 3});
}

void TestScriptEngine()
{
	TestAddStuffToScript();
	TestSetToken();
}

