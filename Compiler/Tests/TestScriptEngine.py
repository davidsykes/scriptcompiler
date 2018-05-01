#!/usr/bin/env python

from ScriptEngine import ScriptEngine

from Assert import AssertNEqual, AssertEqual


def TestCreateScript():
   se = ScriptEngine()
   script = se.CreateScript('test')
   AssertNEqual('tcs1', script, None)

def TestAddStuffToScript():
   se = ScriptEngine()
   script = se.CreateScript('test')
   script.AddTokenInt(1)
   AssertEqual(1, script.GetEndIndex2())
   AssertEqual(4, script.GetEndPC())
   script.AddTokenInt(2)
   AssertEqual(2, script.GetEndIndex2())
   AssertEqual(8, script.GetEndPC())
   script.AddTokenString('fried')
   AssertEqual(3, script.GetEndIndex2())
   AssertEqual(14, script.GetEndPC())

def TestSetToken():
   se = ScriptEngine()
   script = se.CreateScript('test')
   script.AddTokenInt(1)
   script.AddTokenInt(2)
   script.AddTokenInt(3)
   AssertEqual('tst1', script.GetScriptCode(), [1,2,3])
   script.SetToken(1, 4)
   AssertEqual('tst1', script.GetScriptCode(), [1,4,3])

def TestScriptEngine():
   TestCreateScript()
   TestAddStuffToScript()
   TestSetToken()