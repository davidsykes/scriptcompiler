#!/usr/bin/env python

from TokenParser import TokenParser, ValidVariableChar
from Assert import AssertEqual, AssertTrue, AssertFalse

def TestValidVariableChar():
	tp = TokenParser('x')
	AssertTrue('tian1', ValidVariableChar('a'))
	AssertTrue('tian2', ValidVariableChar('z'))
	AssertTrue('tian3', ValidVariableChar('_'))
	AssertFalse('tian4', ValidVariableChar('?'))


def TestBasicTokens():
	tp = TokenParser("var _var1_23\n\n345   // comment\n1234{ }{} +=+-==/\n \r\n\t")
	AssertEqual('ttp1', tp.GetToken(), 'var')
	AssertEqual('ttp2', tp.GetToken(), '_var1_23')
	AssertEqual('ttp3', tp.GetToken(), '345')
	AssertEqual('ttp5', tp.GetToken(), '1234')
	AssertEqual('ttp7', tp.GetToken(), '{')
	AssertEqual('ttp8', tp.GetToken(), '}')
	AssertEqual('ttp7', tp.GetToken(), '{')
	AssertEqual('ttp8', tp.GetToken(), '}')
	AssertEqual('ttp9', tp.GetToken(), '+')
	AssertEqual('ttp10', tp.GetToken(), '=')
	AssertEqual('ttp9', tp.GetToken(), '+')
	AssertEqual('ttp11', tp.GetToken(), '-')
	AssertEqual('ttp12', tp.GetToken(), '==')
	AssertEqual('ttp13', tp.GetToken(), '/')
	AssertEqual(tp.GetToken(), None)

	AssertEqual('ttp14', tp.GetLineNumber(), 7)

def TestMoreTokens():
	tp = TokenParser("&&&")
	AssertEqual(tp.GetToken(), '&&')
	AssertEqual(tp.GetToken(), '&')

def TestOr():
	tp = TokenParser("| || |||")
	AssertEqual(tp.GetToken(), '|')
	AssertEqual(tp.GetToken(), '||')
	AssertEqual(tp.GetToken(), '||')
	AssertEqual(tp.GetToken(), '|')

def TestReplaceToken():
	tp = TokenParser('one two three')
	AssertEqual('trt1', tp.GetToken(), 'one')
	AssertEqual('trt2', tp.GetToken(), 'two')
	tp.ReplaceToken('four')
	AssertEqual('trt3', tp.GetToken(), 'four')
	AssertEqual('trt4', tp.GetToken(), 'three')

def TestScriptDefinitions():
	tp = TokenParser('scriptname(){}')
	AssertEqual(tp.GetToken(), 'scriptname')
	AssertEqual(tp.GetToken(), '(')
	AssertEqual(tp.GetToken(), ')')
	AssertEqual(tp.GetToken(), '{')
	AssertEqual(tp.GetToken(), '}')

def TestStrings():
	tp = TokenParser('bla"string"bla')
	AssertEqual(tp.GetToken(), 'bla')
	AssertEqual(tp.GetToken(), '"string"')
	AssertEqual(tp.GetToken(), 'bla')

def TestTokenParser():
	TestValidVariableChar()
	TestBasicTokens()
	TestReplaceToken()
	TestMoreTokens()
	TestOr()
	TestScriptDefinitions()
	TestStrings()
