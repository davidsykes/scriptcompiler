#!/usr/bin/env python

import traceback
import sys
from CompileError import CompileError

from TestTokenParser import TestTokenParser
from TestCompileEngine import TestCompileEngine
from TestScriptEngine import TestScriptEngine
from TestExpressionParser import TestExpressionParser
from TestOperatorStack import TestOperatorStack

from Assert import AssertFailure

def RunTests():
   try:
      TestTokenParser()
      TestOperatorStack()
      TestScriptEngine()
      TestExpressionParser()
      TestCompileEngine()
   except AssertFailure, e:
      print '**** Assert failure ****'
      print e.value
      print '----- Stack trace ----'
      traceback.print_exc(file=sys.stdout)
   except CompileError, e:
      print '**** Compile error ****'
      print e.value
      print '----- Stack trace ----'
      traceback.print_exc(file=sys.stdout)
