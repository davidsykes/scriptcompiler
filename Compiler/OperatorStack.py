#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

class OperatorStack:
   def __init__(self):
      self.stack = []

   def IsEmpty(self):
      if self.stack:
         return False
      return True

   def GetPrecedence(self):
      if self.stack:
         return self.stack[-1].precedence
      return 0

   def Push(self, operator):
      self.stack.append(operator)

   def Pop(self):
      return self.stack.pop()