// (c) David Sykes 2014
// One more time, for the kids!

#include "Script.h"
#include <map>

#if 0
def WriteInt(file, i):
	file.write(pack('i', i))

def WriteString(file, s):
	file.write(s)
	file.write(pack('b', 0))
#endif


class ScriptEngine
{
public:
	Script&	CreateScript(const std::string& name);

#if 0

	def CreateScript(self, name):
		s = Script(name)
		self.scripts.append(s)
		return s

		def Write(self, file, lstfile):
		d = Dissassembler()
		WriteInt(file, len(self.scripts))
	for s in self.scripts:
		s.Write(file, lstfile, d)
#endif

private:
	std::map<std::string, Script>	m_scripts;

};