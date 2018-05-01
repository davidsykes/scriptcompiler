#!/usr/bin/env python

from ExpressionParser import ExpressionParser
from Interpreter import IC
from MockObjects import MockScript, MockTokenParser, MockVariables
from Assert import AssertTrue, AssertNEqual, AssertEqual

def TestExpressionTerminators():
	ep = ExpressionParser(None)
	AssertTrue('tet1', ep.IsExpressionTerminator(';'))
	AssertTrue('tet2', ep.IsExpressionTerminator(')'))
	AssertTrue('tet3', ep.IsExpressionTerminator(None))

def TestUnaryOperators():
	ep = ExpressionParser(None)
	AssertNEqual('tuo1', ep.GetUnaryOperator('-'), None)
	AssertNEqual('tuo2', ep.GetUnaryOperator('!'), None)
	AssertEqual(ep.GetUnaryOperator('/'), None)

def TestExpressionParserNumeric():
	ep = ExpressionParser(MockVariables())
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('2 + 3 * 4'), script)
	script.CompareScript('texprn', [IC.pushintvalue,
											  2,
											  IC.pushintvalue,
											  3,
											  IC.pushintvalue,
											  4,
											  IC.multiply,
											  IC.add])

def TestExpressionParserVariables():
	variables = MockVariables()
	ep = ExpressionParser(MockVariables(['var1','var2']))
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('var1 / var2'), script)
	script.CompareScript('texprv', [IC.pushvariable,
											  'var1',
											  IC.pushvariable,
											  'var2',
											  IC.devide])

def TestExpressionParserComplex():
	variables = MockVariables(['var1'])
	ep = ExpressionParser(variables)
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('- 2 * ( var1 == 4 )'), script)
	script.CompareScript('texprcx', [IC.pushintvalue,
												2,
												IC.negate,
												IC.pushvariable,
												'var1',
												IC.pushintvalue,
												4,
												IC.equals,
												IC.multiply])


def TestExpressionParser():
	TestExpressionTerminators()
	TestUnaryOperators()
	TestExpressionParserNumeric()
	TestExpressionParserVariables()
	TestExpressionParserComplex()
