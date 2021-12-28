#!/usr/bin/env python

from CompileEngine import CompileEngine
from CompileError import CompileError
from Interpreter import IC
from VariableEngine import VariableEngine

from Assert import AssertEqual, AssertTrue, AssertNEqual
from MockObjects import MockTokenParser, MockVariables, MockScript

#--------------------------------------------------------------------------------------------------------
class MockScriptEngine:
	def __init__(self):
		self.scripts = {}
	def CreateScript(self, name):
		self.scripts[name] = MockScript(name)
		return self.scripts[name]
	def GetScriptCode(self, name):
		return self.scripts[name]

#--------------------------------------------------------------------------------------------------------

def TestEmptyTokenParser():
	tp = MockTokenParser('')
	ce = CompileEngine(tp, None, None)
	ce.Process()
	AssertTrue('tetp', tp.tokenfetched)

def TestInvalidScript():
	tp = MockTokenParser('1completerubbish')
	ce = CompileEngine(tp, MockVariables(), MockScriptEngine())
	try:
		ce.Process()
		AssertTrue('tis', False)
	except CompileError as e:
		AssertEqual(e.value, "01: Unrecognised token '1completerubbish'")

def TestRequireNextToken():
	tp = MockTokenParser('first second')
	ce = CompileEngine(tp, MockVariables(), MockScriptEngine())
	ce.RequireNextToken('first', 'previous')

	try:
		ce.RequireNextToken('third', 'previous')
		AssertTrue('trtnp', False)
	except CompileError as e:
		AssertEqual('trnt1', e.value, "Expected 'third' instead of 'second' after 'previous'")

def TestEmptyScriptFunction():
	tp = MockTokenParser('scriptname ( ) { }')
	se = MockScriptEngine()
	ce = CompileEngine(tp, VariableEngine(), se)
	ce.Process()
	AssertNEqual('tms0', se.GetScriptCode('scriptname'), None)

def TestMissingScriptTerminator():
	tp = MockTokenParser('scriptname ( ) {')
	ce = CompileEngine(tp, VariableEngine(), MockScriptEngine())
	try:
		ce.Process()
		AssertFalse('sef', True)
	except CompileError as e:
		AssertEqual('tmst', e.value, "10: Unexpected end of script")

def TestGlobalVariablesCanBeDeclared():
	tp = MockTokenParser( 'global newglobal ; newglobal = 4 ;')
	ce = CompileEngine(tp, MockVariables(['globalvar'], ['localvar']), None)
	script = MockScript('name')
	ce.CompileSingleExecutionBlock(script)
	ce.CompileSingleExecutionBlock(script)
	script.CompareScript('testdecglobvar', [IC.pushintvalue,
									4,
									IC.popglobalvariable,
									'newglobal'])

def TestGlobalVariablesCanBeAssigned():
	tp = MockTokenParser( 'globalvar = globalvar ;')
	ce = CompileEngine(tp, MockVariables(['globalvar'], ['localvar']), None)
	script = MockScript('name')
	ce.CompileSingleExecutionBlock(script)
	script.CompareScript('testglva', [IC.pushglobalvariable,
									'globalvar',
									IC.popglobalvariable,
									'globalvar'])

def TestLocalVariablesCanBeDeclared():
	tp = MockTokenParser( 'local newlocal ; newlocal = 4 ;')
	ce = CompileEngine(tp, MockVariables(['global'], ['local']), None)
	script = MockScript('name')
	ce.CompileSingleExecutionBlock(script)
	ce.CompileSingleExecutionBlock(script)
	script.CompareScript('testscrlocvar', [IC.pushintvalue,
									4,
									IC.poplocalvariable,
									'newlocal'])

def TestLocalVariablesCanBeAssigned():
	tp = MockTokenParser( 'localvar = localvar ;')
	ce = CompileEngine(tp, MockVariables(['global'], ['localvar']), None)
	script = MockScript('name')
	ce.CompileSingleExecutionBlock(script)
	script.CompareScript('testlocvar', [IC.pushlocalvariable,
									'localvar',
									IC.poplocalvariable,
									'localvar'])

def TestGlobalVariablesCanBeAssigned():
	tp = MockTokenParser( 'globalvar = localvar ;')
	ce = CompileEngine(tp, MockVariables(['globalvar'], ['localvar']), None)
	script = MockScript('name')
	ce.CompileSingleExecutionBlock(script)
	script.CompareScript('testlocvar', [IC.pushlocalvariable,
									'localvar',
									IC.popglobalvariable,
									'globalvar'])

def TestUndefinedGlobalVariablesCanBeAssigned():
	tp = MockTokenParser( 'undefinedglobalvar = localvar ;')
	ce = CompileEngine(tp, MockVariables(['globalvar'], ['localvar']), None)
	script = MockScript('name')
	ce.CompileSingleExecutionBlock(script)
	script.CompareScript('testlocvar', [IC.pushlocalvariable,
									'localvar',
									IC.popglobalvariable,
									'undefinedglobalvar'])

# This test is invalid if unrecognised variables are treated as global variables
#def TestScriptLocalVariablesDiscardedAfterScript():
#	tp = MockTokenParser('script1 ( ) { local localvar ; } script2 ( ) { localvar = 5 ; }')
#	ce = CompileEngine(tp, VariableEngine(), MockScriptEngine())
#
#	try:
#		ce.Process()
#		AssertTrue('tstscrlocdis3', False)
#	except CompileError as e:
#		AssertEqual('tstscrlocdis', e.value, "02: Unrecognised token 'localvar'")

def TestScriptParameters():
	tp = MockTokenParser('scriptname ( param ) { var = param ; }')
	scriptengine = MockScriptEngine()
	ve = VariableEngine()
	ve.AddGlobalVariable('var')
	ce = CompileEngine(tp, ve, scriptengine)
	ce.Process()
	scriptengine.GetScriptCode('scriptname').CompareScript('scrpar', [IC.pushparam,
																		0,
																		IC.popglobalvariable,
																		'var',
																		IC.endscript])

def TestIfStatement():
	tp = MockTokenParser( '{ if ( 1 ) var1 = 11 ; var2 = 12 ; }')
	ce = CompileEngine(tp, MockVariables(['var1','var2',]), None)
	script = MockScript('name')
	try:
		ce.CompileSingleExecutionBlock(script)
	except CompileError as e:
		print('TestIfStatement got a compile error:', e.value)
	script.CompareScript('cmpifst', [IC.pushintvalue,
												1,
												IC.jne,
												17,                #\
												IC.pushintvalue,  # |
												11,               # |
												IC.popglobalvariable,   # |
												'var1',           # |
												IC.pushintvalue,  #/
												12,
												IC.popglobalvariable,
												'var2'])

def TestIfElseStatement():
	tp = MockTokenParser( 'if ( 1 ) var = 11 ; else var = 12 ;')
	ce = CompileEngine(tp, MockVariables(['var','mock']), None)
	script = MockScript('name')
	try:
		ce.CompileSingleExecutionBlock(script)
	except CompileError as e:
		print('TestIfElseStatement got a compile error:', e.value)
	script.CompareScript('cmpifest', [IC.pushintvalue,
												 1,
												 IC.jne,
												 24,               #\
												 IC.pushintvalue,  # |
												 11,               # |
												 IC.popglobalvariable,   # |
												 'var',            # |
												 IC.jall,          # |
												 16,                # |  #\
												 IC.pushintvalue,  #/   # |
												 12,                    # |
												 IC.popglobalvariable,        # |
												 'var'])                # |
												                        #/
def TestIfElseifStatement():
	tp = MockTokenParser( 'if ( 1 ) var = 11 ; elseif ( 1 ) var = 12 ; else var = 13 ;')
	ce = CompileEngine(tp, MockVariables(['var','mock']), None)
	script = MockScript('name')
	try:
		ce.CompileSingleExecutionBlock(script)
	except CompileError as e:
		print('TestIfElseStatement got a compile error:', e.value)
	script.CompareScript('cmpifelif', [IC.pushintvalue,
												 1,
												 IC.jne,
												 24,                #\
												 IC.pushintvalue,   # |
												 11,                # |
												 IC.popglobalvariable,    # |
												 'var',             # |
												 IC.jall,           # | \
												 56,                # | |
												 IC.pushintvalue,   #/  |
												 1,                 #   |
												 IC.jne,            #   |
												 24,                #   | \
												 IC.pushintvalue,   #   | |
												 12,                #   | |
												 IC.popglobalvariable,    #   | |
												 'var',             #   | |
												 IC.jall,           #   | | \
												 16,                #   | | |
												 IC.pushintvalue,   #   | / |
												 13,                #   |   |
												 IC.popglobalvariable,    #   |   |
												 'var'])            #   |   |
												                    #  /    /
def TestEngineFunctionInvalid():
	tp = MockTokenParser( 'engineFunction ;')
	try:
		script = MockScript('name')
		ce = CompileEngine(tp, MockVariables([],[],[['engineFunction',0]]), None)
		ce.CompileSingleExecutionBlock(script)
		AssertTrue(False)
	except CompileError as e:
		pass

def TestFnRoutineDropSkipJump():
	tp = MockTokenParser( 'engineFunction ( ) ;')
	ce = CompileEngine(tp, MockVariables([],[],[['engineFunction',0]]), None)
	script = MockScript('name')
	try:
		ce.CompileSingleExecutionBlock(script)
	except CompileError as e:
		print('TestFnRoutineDropSkipJump got a compile error:', e.value)
	script.CompareScript('fndsk', [IC.callfnroutine,
									0,
									'engineFunction',
									IC.dropskippausenonzero,
									-27])

def TestPauseStatement():
	tp = MockTokenParser( 'pause ;')
	script = MockScript('name')
	ce = CompileEngine(tp, VariableEngine(), None)
	ce.CompileSingleExecutionBlock(script)
	script.CompareScript('pause', [IC.pause])

def TestCompileEngine():
	TestEmptyTokenParser()
	TestInvalidScript()
	TestRequireNextToken()
	TestEmptyScriptFunction()
	TestMissingScriptTerminator()
	TestGlobalVariablesCanBeDeclared()
	TestGlobalVariablesCanBeAssigned()
	TestLocalVariablesCanBeDeclared()
	TestLocalVariablesCanBeAssigned()
	#TestScriptLocalVariablesDiscardedAfterScript()
	TestScriptParameters()
	TestIfStatement()
	TestIfElseStatement()
	TestIfElseifStatement()
	TestEngineFunctionInvalid()
	TestFnRoutineDropSkipJump()
	TestPauseStatement()
	TestGlobalVariablesCanBeAssigned()
	TestUndefinedGlobalVariablesCanBeAssigned()
