#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

import sys
import os
from Parameters import Parameters, ParamError
from CompileEngine import CompileEngine
from CompileError import CompileError
from TokenParser import TokenParser
from VariableEngine import VariableEngine
from ScriptEngine import ScriptEngine

def Useage(mess = None):
	print 'Useage: ' + sys.argv[0] + " file"
	if mess:
		print
		print mess
		sys.exit(-1)
	sys.exit(0)

def Quit(mess):
	print mess
	sys.exit(-1)

try:
	p = Parameters(['test'],'[variables,functions]','[undefined]', sys.argv[1:])
except ParamError, e:
	Useage('Param error: ' + e.value )

if p.GetSwitch('test'):
	sys.path.append('./Tests')
	from Tests import RunTests
	RunTests()
	sys.exit(0)

if len(p.GetParameters()) < 1:
	Useage('No script to compile')

if p.GetOption('variables') == None and p.GetOption('functions') == None:
	Useage('No variable or functions file specified')

variableengine = VariableEngine()
try:
	if p.GetOption('variables') != None:
		variableengine.LoadXml(p.GetOption('variables'))
	if p.GetOption('functions') != None:
		variableengine.LoadXml(p.GetOption('functions'))
except CompileError, e:
	Quit(''.join([p.GetOption('variables'), ': ', e.value]))

scriptengine = ScriptEngine()

for script in p.GetParameters():
	try:
		filedata = open(script).read()
	except IOError, e:
		Useage(e)
	tokenparser = TokenParser(filedata)
	e = CompileEngine(tokenparser, variableengine, scriptengine)
	try:
		e.Process()
		try:
			(a,b) = os.path.splitext(script)
			target = a + '.obj'
			print 'target', target
			objf = open(target, 'w')
			lstf = open(a+'.lst', 'w')
			scriptengine.Write(objf, lstf)
		except IOError, e:
			Useage(e)
	except CompileError, e:
		Quit(''.join([script, '(', str(e.line), '): ', e.value]))