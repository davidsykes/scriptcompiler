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
from NullFileWrapper import NullFileWrapper

def Useage(mess = None):
	print('Useage: ' + sys.argv[0] + " {script file} -variables {variable file} -functions {functions file}")
	print("Options: -lst : Ouptut debug information")
	if mess:
		print()
		print(mess)
		sys.exit(-1)
	sys.exit(0)

def Quit(mess):
	print(mess)
	sys.exit(-1)

def fetch_output_folder(parameters):
	return p.GetOption('output')

def make_output_script_path(script_path, output_folder):
	(full_path, extension) = os.path.splitext(script)
	(folder, file_name) = os.path.split(full_path)
	if output_folder:
		return os.path.join(output_folder, file_name)
	return full_path

def get_list_file(path, create_list_file_path_flag):
	if create_list_file_path_flag:
		return open(output_script_path + '.lst', 'w')

try:
	p = Parameters(['test','lst'],'[variables,functions,output]','[undefined]', sys.argv[1:])
except ParamError as e:
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

output_folder = fetch_output_folder(p)

variableengine = VariableEngine()
try:
	if p.GetOption('variables') != None:
		variableengine.LoadXml(p.GetOption('variables'))
	if p.GetOption('functions') != None:
		variableengine.LoadXml(p.GetOption('functions'))
except CompileError as e:
	Quit(''.join([p.GetOption('variables'), ': ', e.value]))

scriptengine = ScriptEngine()

for script in p.GetParameters():
	try:
		filedata = open(script).read()
	except IOError as e:
		Useage(e)
	tokenparser = TokenParser(filedata)
	e = CompileEngine(tokenparser, variableengine, scriptengine)
	try:
		e.Process()
		try:
			output_script_path = make_output_script_path(script, output_folder)
			target = output_script_path + '.bytes'
			objf = open(target, 'wb')
			listFile = NullFileWrapper(get_list_file(output_script_path, p.GetSwitch('lst')))
			scriptengine.Write(objf, listFile)
		except IOError as e:
			Useage(e)
	except CompileError as e:
		Quit(''.join(['Error:', script, '(', str(e.line), '): ', e.value]))
