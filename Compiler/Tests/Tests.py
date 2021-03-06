#!/usr/bin/env python

import sys
sys.path.append("../")

import traceback
import sys
from CompileError import CompileError

from TestTokenParser import TestTokenParser
from TestCompileEngine import TestCompileEngine
from TestScriptEngine import TestScriptEngine
from TestExpressionParser import TestExpressionParser
from TestOperatorStack import TestOperatorStack
from TestVariableEngine import TestVariableEngine

from Assert import AssertFailure

def RunTests():
   try:
      TestTokenParser()
      TestOperatorStack()
      TestVariableEngine()
      TestScriptEngine()
      TestExpressionParser()
      TestCompileEngine()
   except AssertFailure as e:
      print('**** Assert failure ****')
      print(e.value)
      print()
      print('----- Stack trace ----')
      traceback.print_exc(file=sys.stdout)
   except CompileError as e:
      print('**** Compile error ****')
      print(e.value)
      print('----- Stack trace ----')
      traceback.print_exc(file=sys.stdout)

RunTests()