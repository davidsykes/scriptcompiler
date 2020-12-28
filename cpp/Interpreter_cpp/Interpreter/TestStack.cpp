#include "VariableStack.h"
#include "Assert.h"
#include "InterpreterException.h"

using namespace Script;


static void TestPushPopInt()
{
	VariableStack stack;

	stack.Push(Variable(42));
	AssertEqual(42, stack.Pop().Int());
}

static void TestPushPopString()
{
	VariableStack stack;

	stack.Push(Variable("42"));
	AssertEqual("42", stack.Pop().String());
}

static void TestUnderFlow()
{
	try
	{
		VariableStack stack;
		stack.Pop();
	}
	catch (InterpreterException)
	{
		return;
	}
	catch (...)
	{
	}
	Assert();
}

static void TestGetHead()
{
	VariableStack stack;

	try
	{
		stack.GetHead();
		Assert();
	}
	catch (InterpreterException){}
	
	stack.Push(Variable(42));
	AssertEqual(42, stack.GetHead().Int());

	stack.Push(Variable(24));
	AssertEqual(24, stack.GetHead().Int());
}

static void TestSetHead()
{
	VariableStack stack;

	try
	{
		stack.SetHead(Variable(10));
		Assert();
	}
	catch (InterpreterException){}

	stack.Push(Variable(1));
	stack.SetHead(Variable(10));
	stack.Push(Variable(2));
	stack.SetHead(Variable(20));
	
	AssertEqual(20, stack.Pop().Int());
	AssertEqual(10, stack.Pop().Int());
}

void TestStack()
{
	TestPushPopInt();
	TestPushPopString();
	TestUnderFlow();
	TestGetHead();
	TestSetHead();
}