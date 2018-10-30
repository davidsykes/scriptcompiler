#!/usr/bin/env python

from VariableEngine import VariableEngine
from Assert import AssertEqual, AssertTrue, AssertFalse, AssertAlways, AssertContains
from CompileError import CompileError

def TestGlobalVariableCanBeDeclared():
	ve = VariableEngine()
	ve.AddGlobalVariable('globalvar')
	AssertTrue('tgvd', ve.IsGlobalVariable('globalvar'))

def TestGlobalVariableCantBeDeclaredTwice():
	ve = VariableEngine()
	ve.AddGlobalVariable('globalvar')
	try:
		ve.AddGlobalVariable('globalvar')
	except CompileError, e:
		AssertContains('tgvc', e.value, 'Variable with name globalvar defined twice')
		return
	AssertAlways('Exception expected when declaring a global variable twice')

def TestVariableEngine():
	TestGlobalVariableCanBeDeclared()
	TestGlobalVariableCantBeDeclaredTwice()
