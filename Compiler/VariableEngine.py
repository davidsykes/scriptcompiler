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
		if name not in ['xml', 'globals', 'flag', 'functions', 'function']:
			raise CompileError(''.join(["Element name '", name, "' is not recognised"]))
		if name == 'flag':
			try:
				name = attributes['name']
				value = attributes['value']
				self.variables.AddGlobalVariable(name)
			except KeyError:
				raise CompileError("Missing name or value in variable definition" + self.GetLocatorInfo())
		elif name == 'function':
			try:
				name = attributes['name']
				try:
					parametercount = int(attributes['parameters'])
				except KeyError:
					raise CompileError("Missing parameter count in function definition" + self.GetLocatorInfo())
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
		self.variables = {}
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
		if name in self.variables:
			raise CompileError(''.join(['Variable with name ', name, ' defined twice'])  + self.GetLocatorInfo())
		self.variables[name] = True

	def IsGlobalVariable(self, name):
		return name in self.variables

	def AddFunction(self, name, parameterCount):
		self.engineFunctions[name] = parameterCount;

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
