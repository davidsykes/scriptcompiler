

#include "Variable.h"
#include "Assert.h"

using namespace Script;

static void TestDefaultConstruct()
{
	Variable v;
	AssertEqual(0, v.Int());
	AssertEqual("", v.String());
}

static void TestIntConstruct()
{
	Variable v(42);
	AssertEqual(42, v.Int());
	AssertEqual("", v.String());
}

static void TestIntAdd()
{
	Variable v(42);
	Variable x = v + 1;
	AssertEqual(43, x.Int());
}

static void TestStringConstruct()
{
	Variable v("string");
	AssertEqual("string", v.String());
	AssertEqual(0, v.Int());
}

static void TestStringAdd()
{
	Variable v1("s1");
	Variable v2(v1 + "s2");
	AssertEqual("s1s2", v2.String());
	AssertEqual(0, v2.Int());
}

static void TestCrossAddition()
{
	Variable i(3);
	Variable s("three");

	AssertEqual(3, (s+i).Int());
	AssertEqual("three", (s+i).String());

	AssertEqual(3, (i+s).Int());
	AssertEqual("three", (i+s).String());
}

static void TestEqualsInt()
{
	Variable v1(1);
	Variable v2(2);
	Variable v3(2);
	Assert(!(v1 == v2));
	Assert(v2 == v3);
}

static void TestEqualsString()
{
	Variable v1("1");
	Variable v2("2");
	Variable v3("2");
	Assert(!(v1 == v2));
	Assert(v2 == v3);
}

static void TestGTLT(const Variable& v1, const Variable& v2, const Variable& v3)
{
	// <
	Assert(!(v1 > v2));
	Assert(v2 > v1);

	Assert(!(v2 > v3));
	Assert(!(v3 > v2));
	// <=
	Assert(!(v1 >= v2));
	Assert(v2 >= v1);

	Assert((v2 >= v3));
	Assert((v3 >= v2));
	// >
	Assert( (v1 < v2));
	Assert(!(v2 < v1));

	Assert(!(v2 < v3));
	Assert(!(v3 < v2));
	// >=
	Assert( (v1 <= v2));
	Assert(!(v2 <= v1));

	Assert( (v2 <= v3));
	Assert( (v3 <= v2));
}

static void TestGTLTInt()
{
	Variable v1(1);
	Variable v2(2);
	Variable v3(2);
	TestGTLT(v1,v2,v3);
}

static void TestGTLTString()
{
	Variable v1("1");
	Variable v2("2");
	Variable v3("2");
	TestGTLT(v1,v2,v3);
}

void TestVariables()
{
	TestDefaultConstruct();
	TestIntConstruct();
	TestIntAdd();
	TestStringConstruct();
	TestStringAdd();
	TestCrossAddition();
	TestEqualsInt();
	TestEqualsString();
	TestGTLTInt();
	TestGTLTString();
}