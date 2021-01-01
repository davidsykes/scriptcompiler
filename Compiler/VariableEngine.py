#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

import os
from CompileError import CompileError
import xml.sax.handler


class XMLHandler(xml.sax.handler.ContentHandler):
	def __init__(self, variables):
		self.inTitle = 0
		self.variables = variables

	def startElement(self, name, attributes):
		if name not in ['xml', 'globals', 'global', 'local', 'functions', 'function']:
			raise CompileError(''.join(["Element name '", name, "' is not recognised"]))
		if name == 'global':
			try:
				name = attributes['name']
				self.variables.AddGlobalVariable(name)
			except KeyError:
				raise CompileError("Missing name in variable definition" + self.GetLocatorInfo())
		elif name == 'local':
			try:
				name = attributes['name']
				self.variables.AddLocalVariable(name)
			except KeyError:
				raise CompileError("Missing name in variable definition" + self.GetLocatorInfo())
		elif name == 'function':
			try:
				name = attributes['name']
				parametercount = 0
				if 'parameters' in attributes:
					try:
						parametercount = int(attributes['parameters'])
					except:
						raise CompileError(''.join(["Invalid parameter count '", attributes['parameters'], "' ", self.GetLocatorInfo()]))
				self.variables.AddFunction(name, parametercount)
			except KeyError:
				raise CompileError("Missing name or parameter count in function definition" + self.GetLocatorInfo())
 
	def characters(self, data):
		#print ''.join(['Characters "', data, '"'])
		pass
 
	def endElement(self, name):
		#print "EndElement", name
		pass

	def GetLocatorInfo(self):
		if self._locator != None:
			return ''.join([': Line ', str(self._locator.getLineNumber()), ' column ', str(self._locator.getColumnNumber())])
		return ''

class VariableEngine:
	def __init__(self):
		self.globalvariables = {}
		self.localvariables = {}
		self.scriptlocalvariables = {}
		self.scriptparameters = {}
		self.engineFunctions = {}

	def LoadXml(self, path):
		if not os.path.exists(path):
			raise CompileError(''.join(["Variable file '", path, "' not found"]))
		parser = xml.sax.make_parser(  )
		handler = XMLHandler(self)
		parser.setContentHandler(handler)
		parser.parse(path)

	def AddGlobalVariable(self, name):
		if name in self.globalvariables or name in self.localvariables or name in self.scriptlocalvariables:
			raise CompileError(''.join(['Variable with name ', name, ' defined twice']))
		self.globalvariables[name] = True

	def IsGlobalVariable(self, name):
		return name in self.globalvariables

	def IsLocalVariable(self, name):
		return name in self.localvariables or name in self.scriptlocalvariables

	def AddLocalVariable(self, name):
		if name in self.globalvariables or name in self.localvariables:
			raise CompileError(''.join(['Variable with name ', name, ' defined twice']))
		self.localvariables[name] = True

	def AddScriptLocalVariable(self, name):
		if name in self.globalvariables or name in self.localvariables or name in self.scriptlocalvariables:
			raise CompileError(''.join(['Variable with name ', name, ' defined twice']))
		self.scriptlocalvariables[name] = True

	def ClearScriptLocalVariables(self):
		self.scriptlocalvariables = {}

	def AddFunction(self, name, parameterCount):
		self.engineFunctions[name] = parameterCount

	def IsFunction(self, name):
		return name in self.engineFunctions

	def ClearScriptParameters(self):
		self.scriptparameters = {}

	def AddScriptParameter(self, name):
		parameterNumber = len(self.scriptparameters)
		self.scriptparameters[name] = parameterNumber

	def GetScriptParameter(self, name):
		if name in self.scriptparameters:
			return self.scriptparameters[name]
		return None
