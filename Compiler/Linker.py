#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

import sys
#import os
import struct
from Parameters import Parameters, ParamError
from struct import pack

def Useage(mess = None):
	print('Useage: ' + sys.argv[0] + " [files to link] -target targetfile")
	if mess:
		print
		print(mess)
		sys.exit(-1)
	sys.exit(0)

def Quit(mess):
	print(mess)
	sys.exit(-1)

def ReadInt(file):
	return struct.unpack('i', file.read(4))[0]

def WriteInt(file, i):
	file.write(pack('i', i))

try:
	p = Parameters(['test','verbose'],'[target]','[xxx]', sys.argv[1:])
except ParamError, e:
	Useage('Param error: ' + e.value )

#if p.GetSwitch('test'):
#	sys.path.append('./Tests')
#	from Tests import RunTests
#	RunTests()
#	sys.exit(0)

if len(p.GetParameters()) < 1:
	Useage('No files to link')

targetfile = None
if p.GetOption('target') != None:
	targetfile = open(p.GetOption('target'), "wb")

scripts = {}

for scriptfile in p.GetParameters():
	try:
		print('=======')
		print('File:', scriptfile)
		file = open(scriptfile, "rb")

		scriptcount = ReadInt(file)
		print('Script count:', scriptcount)

		for x in range(0, scriptcount):
			namelength = ReadInt(file)
			print('namelength', namelength)
			scriptname = file.read(namelength)
			print('scriptname', scriptname)
			scriptlength = struct.unpack('i', file.read(4))[0]
			print('scriptlength', scriptlength)
			scriptcode = file.read(scriptlength)
			scripts[scriptname] = scriptcode

	except IOError, e:
		Useage(e)

if targetfile:
	print('>>>>>>>', p.GetOption('target'))
	print('script count', len(scripts))
	WriteInt(targetfile, len(scripts))

	for script in scripts.iteritems():
		WriteInt(targetfile, len(script[0]))
		targetfile.write(script[0])
		WriteInt(targetfile, len(script[1]))
		targetfile.write(script[1])

try:
	targetfile = open(p.GetOption('target'), "wb")
except IOError, e:
	Useage(e)
