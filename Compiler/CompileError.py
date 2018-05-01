#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

class CompileError(Exception):
	 def __init__(self, value, line=0):
		  self.value = value
		  self.line = line

