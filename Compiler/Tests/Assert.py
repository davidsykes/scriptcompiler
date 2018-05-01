#!/usr/bin/env python

class AssertFailure(Exception):
	 def __init__(self, value):
		  self.value = value


def AssertTrue(m,b=None):
	if b == None:
		b = m
		m = ''
	if not b:
		raise AssertFailure('AssertTrue Failure: ' + m)

def AssertFalse(m,b):
	if b:
		print '------------------------------------------------------'
		print 'AssertFalse Failure', m
		print '------------------------------------------------------'

def AssertEqual(m,a,b=None):
	if b == None:
		b = a
		a = m
		m = ''
	if a != b:
		raise AssertFailure(''.join(['AssertEqual Failure: ', m, "\nGot '", str(a), "'\nexp '", str(b), "'"]))

def AssertNEqual(m,a,b):
	if a == b:
		raise AssertFailure(''.join(['AssertNEqual fail ', m, ' Did not want to get "', str(a), '"']))
#      print '------------------------------------------------------'
#      print 'Assert Failure', m
#      print 'Did not want to get "' + str(a) + '"'
#      print '------------------------------------------------------'

def AssertContains(m,a,b):
	if a.find(b) < 0:
		print '------------------------------------------------------'
		print 'AssertContains Failure', m
		print 'Exp "' + str(b) + '"'
		print 'Got "' + str(a) + '"'
		print '------------------------------------------------------'
