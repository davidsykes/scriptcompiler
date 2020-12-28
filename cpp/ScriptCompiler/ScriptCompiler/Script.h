// (c) David Sykes 2014
// One more time, for the kids!

#pragma once

#include <string>
#include <vector>

class Script
{
public:
			Script(const std::string& name);

	void	AddTokenInt(int token);
	void	AddTokenString(const std::string& token);
	void	SetToken(int index, __int32 value);
	int		GetEndIndex() const;
	int		GetEndPC() const;

#ifdef _DEBUG
	const std::vector<__int32>& GetScriptCode()const{ return m_code; }
#endif
#if 0
	def AddTokenInt(self, token) :
		self.code.append(token)
		self.pc = self.pc + 4

		def AddTokenString(self, token) :
		self.code.append(token)
		self.pc = self.pc + len(token) + 1

		def GetEndPC(self) :
		return self.pc

		def GetEndIndex2(self) :
		return len(self.code)

		def GetScriptCode(self) :
		return self.code

		def SetToken(self, index, value) :
		self.code[index] = value

		def Write(self, objfile, lstfile, d) :
		lstfile.write(''.join(['Script ', self.name, "\n"]))

# Name length, followed by name
		WriteInt(objfile, len(self.name))
		objfile.write(self.name)
		scriptsizeposition = objfile.tell()
		WriteInt(objfile, 0)
		ip = 0
		nextisparam = False
	for t in self.code:
	if type(t) == int :
	if nextisparam :
		lstfile.write(''.join([str(ip), ': ', str(t), "\t\t", str(t)]))
		nextisparam = False
	else :
	lstfile.write(''.join([str(ip), ': ', str(t), "\t\t", d.codes[t][0]]))
	if d.codes[t][1] :
		nextisparam = True
		WriteInt(objfile, t)
		ip = ip + 4
		elif type(t) == str :
		lstfile.write(''.join([str(ip), ": '", t, "'"]))
		nextisparam = False
		WriteString(objfile, t)
		ip = ip + len(t) + 1
	else:
	print type(t)
		lstfile.write("\n");
# Go back and put the script length in
	curpos = objfile.tell()
		objfile.seek(scriptsizeposition);
	WriteInt(objfile, ip)
		objfile.seek(curpos);
#endif

private:
	const std::string&	m_name;
	int					m_pc;
	std::vector<__int32>m_code;

};

