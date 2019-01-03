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
	ep.ParseExpression(MockTokenParser('2 + 3 * 4 - 5'), script)
	script.CompareScript('texprn', [IC.pushintvalue,
											  2,
											  IC.pushintvalue,
											  3,
											  IC.pushintvalue,
											  4,
											  IC.multiply,
											  IC.add,
											  IC.pushintvalue,
											  5,
											  IC.subtract
											  ])

def TestExpressionParserString():
	ep = ExpressionParser(MockVariables())
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('"Hello" + "World"'), script)
	script.CompareScript('stringexp', [IC.pushstring,
											  'Hello',
											  IC.pushstring,
											  'World',
											  IC.add,
											  ])

def TestExpressionParserVariables():
	ep = ExpressionParser(MockVariables(['var1','var2']))
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('var1 / var2'), script)
	script.CompareScript('texprv', [IC.pushglobalvariable,
											  'var1',
											  IC.pushglobalvariable,
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
												IC.pushglobalvariable,
												'var1',
												IC.pushintvalue,
												4,
												IC.equals,
												IC.multiply])

def TestFnRoutineNoParameters():
	variables = MockVariables(['var1'], [], [['engineFunction',0]])
	ep = ExpressionParser(variables)
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('engineFunction ( )'), script)
	script.CompareScript('fnnop', [IC.callfnroutine,
									0,
									'engineFunction'])

def TestHashCalculator():
	ep = ExpressionParser(MockVariables())
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('[ hashtext ]'), script)
	script.CompareScript('hash', [IC.pushintvalue,
											  1976965134
											  ])

def TestHashCalculatorUsesSignedCRC32():
	ep = ExpressionParser(MockVariables())
	script = MockScript('name')
	ep.ParseExpression(MockTokenParser('[ hello-world ]'), script)
	script.CompareScript('hashs', [IC.pushintvalue,
											  -1311505829 #2983461467
											  ])

def TestExpressionParser():
	TestExpressionTerminators()
	TestUnaryOperators()
	TestExpressionParserNumeric()
	TestExpressionParserString()
	TestExpressionParserVariables()
	TestExpressionParserComplex()
	TestFnRoutineNoParameters()
	TestHashCalculator()
	TestHashCalculatorUsesSignedCRC32()
