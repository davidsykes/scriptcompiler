#!/usr/bin/env python

from OperatorStack import OperatorStack
from ExpressionParser import Operator
from Assert import AssertEqual, AssertTrue

def TestEmptyStack():
   os = OperatorStack()
   AssertTrue('tose1', os.IsEmpty())
   AssertEqual('tose2', os.GetPrecedence(), 0)

def TestPushAndPop():
   os = OperatorStack()
   os.Push(Operator(1,1))
   AssertEqual('tpap1', os.GetPrecedence(), 1)
   os.Push(Operator(2,2))
   AssertEqual('tpap2', os.GetPrecedence(), 2)

   AssertEqual('tpap3', os.Pop().scriptcommand, 2)
   AssertEqual('tpap3', os.Pop().scriptcommand, 1)
   AssertTrue('tose1', os.IsEmpty())
   AssertEqual('tose2', os.GetPrecedence(), 0)


def TestOperatorStack():
   TestEmptyStack()
   TestPushAndPop()
