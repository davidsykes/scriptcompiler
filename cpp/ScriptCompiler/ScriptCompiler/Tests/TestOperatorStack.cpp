//#!/usr/bin/env python

#include "..\OperatorStack.h"
#include "TDDAssert.h"


void TestEmptyStack()
{
	OperatorStack os;
		AssertTrue(os.IsEmpty());
		AssertEqual(os.GetPrecedence(), 0);
}

void TestPushAndPop()
{
	OperatorStack os;
	os.Push(Operator(1, 1));
	AssertEqual(os.GetPrecedence(), 1);
	os.Push(Operator(2, 2));
	AssertEqual(os.GetPrecedence(), 2);

	AssertEqual(os.Pop().scriptCommand, 2);
	AssertEqual(os.Pop().scriptCommand, 1);
	AssertTrue(os.IsEmpty());
	AssertEqual(os.GetPrecedence(), 0);
}

void TestOperatorStack()
{
	TestEmptyStack();
	TestPushAndPop();
}


