#!/usr/bin/env python

# (c) David Sykes 2013
# One more time, for the kids!

class ParamError(Exception):
    def __init__(self, value):
        self.value = value


class Parameters:
   def __init__(self, switches, singleoptions, multipleoptions, args):
      self.switches = {}
      self.singleoptions = {}
      self.multipleoptions = {}
      self.parameters = []

      i = 0
      while i < len(args):
         carg = args[i]
         if carg[0] == '-':
            coption = carg[1:]
            # Is this a switch
            try:
               oi = switches.index(coption)
               self.switches[coption] = True
            except ValueError:
               try:
                  oi = singleoptions.index(coption)
                  self.singleoptions[coption] = args[i+1]
               except ValueError:
                  try:
                     oi = multipleoptions.index(coption)
                     try:
                        self.multipleoptions[coption].append(args[i+1])
                     except KeyError:
                        self.multipleoptions[coption] = [args[i+1]]
                  except ValueError:
                     raise ParamError("".join(["Invalid option '",coption]))
               except IndexError:
                  return
               i = i + 1
         else:
            self.parameters.append(carg)
         i = i + 1

   def GetParameters(self):
      return self.parameters

   def GetSwitch(self, name):
      try:
         return self.switches[name]
      except KeyError:
         return False

   def GetOption(self, name):
      try:
         return self.singleoptions[name]
      except KeyError:
         try:
            return self.multipleoptions[name]
         except KeyError:
            return None