#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

from struct import pack
from Interpreter import Dissassembler

def WriteInt(file, i):
	file.write(pack('i', i))

def WriteString(file, s):
	file.write(s.encode())
	file.write(pack('b', 0))

class Script(object):
	def __init__(self, name):
		self.name = name
		self.code = []
		self.pc = 0

	def AddTokenInt(self, token):
		self.code.append(token)
		self.pc = self.pc + 4

	def AddTokenString(self, token):
		self.code.append(token)
		self.pc = self.pc + len(token) + 1

	def GetEndPC(self):
		return self.pc

	def GetEndIndex2(self):
		return len(self.code)

	def GetScriptCode(self):
		return self.code

	def SetToken(self, index, value):
		self.code[index] = value

	def Write(self, objfile, lstfile, d):
		lstfile.write(''.join(['Script ', self.name, "\n"]))

		# Name length, followed by name
		WriteInt(objfile, len(self.name))
		objfile.write(self.name.encode())
		scriptsizeposition = objfile.tell()
		WriteInt(objfile, 0)
		ip = 0
		nextisparam = False
		for t in self.code:
			if type(t) == int:
				if nextisparam:
					lstfile.write(''.join([str(ip), ': ', str(t), "\t\t", str(t)]))
					nextisparam = False
				else:
					lstfile.write(''.join([str(ip), ': ', str(t), "\t\t", d.codes[t][0]]))
					if d.codes[t][1]:
						nextisparam = True
				WriteInt(objfile, t)
				ip = ip + 4
			elif type(t) == str:
				lstfile.write(''.join([str(ip), ": '", t, "'"]))
				nextisparam = False
				WriteString(objfile, t)
				ip = ip + len(t) + 1
			else:
				print(type(t))
			lstfile.write("\n")
		# Go back and put the script length in
		curpos = objfile.tell()
		objfile.seek(scriptsizeposition)
		WriteInt(objfile, ip)
		objfile.seek(curpos)

class ScriptEngine:
	def __init__(self):
		self.scripts = []

	def CreateScript(self, name):
		s = Script(name)
		self.scripts.append(s)
		return s

	def Write(self, file, lstfile):
		d = Dissassembler()
		WriteInt(file, len(self.scripts))
		for s in self.scripts:
			s.Write(file, lstfile, d)