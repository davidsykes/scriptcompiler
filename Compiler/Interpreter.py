#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!


class IC:
	pushintvalue = 1
	pushparam = 2
	pushstring = 3
	pushvariable = 4
	popvariable = 5
	jne = 6
	jtrue = 7
	jall = 8
	add = 9
	subtract = 10
	multiply = 11
	devide = 12
	negate = 13
	logicalnot = 14
	lt = 15
	gt = 16
	lte = 17
	gte = 18
	equals = 19
	logicaland = 20
	logicalor = 21
	callfnroutine = 22
	dropstackvalue = 23
	endscript = 24

class Dissassembler(object):
	def __init__(self):
		self.codes = {}
		self.codes[IC.pushintvalue]		= ['pushintvalue', True]
		self.codes[IC.pushparam]		= ['pushparam', True]
		self.codes[IC.pushstring]		= ['pushstring', True]
		self.codes[IC.pushvariable]		= ['pushvariable', True]
		self.codes[IC.popvariable]		= ['popvariable', True]
		self.codes[IC.jne]				= ['jne', True]
		self.codes[IC.jtrue]			= ['jtrue', True]
		self.codes[IC.jall]				= ['jall', True]
		self.codes[IC.add]				= ['add', False]
		self.codes[IC.subtract]			= ['subtract', False]
		self.codes[IC.multiply]			= ['multiply', False]
		self.codes[IC.devide]			= ['devide', False]
		self.codes[IC.negate]			= ['negate', False]
		self.codes[IC.logicalnot]		= ['logicalnot', False]
		self.codes[IC.lt]				= ['lt', False]
		self.codes[IC.gt]				= ['gt', False]
		self.codes[IC.lte]				= ['lte', False]
		self.codes[IC.gte]				= ['gte', False]
		self.codes[IC.equals]			= ['equals', False]
		self.codes[IC.logicaland]		= ['logicaland', False]
		self.codes[IC.logicalor]		= ['logicalor', False]
		self.codes[IC.callfnroutine]	= ['callfnroutine', True]
		self.codes[IC.dropstackvalue]	= ['dropstackvalue', False]
		self.codes[IC.endscript]		= ['endscript', False]
