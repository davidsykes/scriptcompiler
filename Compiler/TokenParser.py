#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

import re

def ValidVariableChar(ch):
	return (ch >= 'a' and ch <= 'z') or (ch >= 'A' and ch <= 'Z') or (ch == '_')

class TokenParser:
	def __init__(self, filedata):
		self.lines = filedata.splitlines()
		self.curlinenumber = 0
		self.tokenLineNumber = 0
		if len(self.lines) > 0:
			self.curline = self.lines[0]
		else:
			self.curline = ''
		self.replacedtoken = None
		self.debug = False

	def GetFirstChar(self):
		while self.curlinenumber < len(self.lines):
			pos = 0
			while pos < len(self.curline):
				if self.curline[pos] in " \t\r\n":
					pos = pos + 1
				else:
					self.curline = self.curline[pos:]
					return self.curline[0]
			self.NextLine()
		return None

	def NextLine(self):
		self.curlinenumber = self.curlinenumber + 1
		if self.curlinenumber < len(self.lines):
			self.curline = self.lines[self.curlinenumber]
		else:
			self.curline = None

	def GetLineNumber(self):
		return self.tokenLineNumber + 1

	def MoveDataOn(self, tokenend):
		if tokenend >= len(self.curline):
			self.NextLine()
		else:
			self.curline = self.curline[tokenend:]

	def GetToken(self):
		token = None
		if self.replacedtoken:
			token = self.replacedtoken
			self.replacedtoken = None
		else:
			self.GetFirstChar()
			while self.curline and self.curline[0:2] == "//":
				self.NextLine()
				self.GetFirstChar()
			# 		(a|b|c)
			self.tokenLineNumber = self.curlinenumber
			if self.curline:
				m = re.search('^([a-zA-Z_][a-zA-Z0-9_]*|[0-9]+|[>=<]=?|&&?|[,{}\+-]|\|\|?|;|\(|\)|\[|\]|"[^"]*")', self.curline)
				if m:
					token = m.group(1)
				else:
					token = self.curline
			if token:
				self.MoveDataOn(len(token))
		if self.debug:
			print 'Token', token
		return token

	def ValidVariableChar(self, ch):
		# Removes need for compile engine to depend on token parser
		return ValidVariableChar(ch)

	def ReplaceToken(self, token):
		self.replacedtoken = token