// (c) David Sykes 2013
// One more time, for the kids!

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "MockInterpreter.h"

//void	RunTests();
int	ReadInt(std::ifstream& is);


int main(int argc, char* argv[])
{
	try
	{
		//RunTests();

		if (argc != 3)
		{
			throw std::exception("Missing script file or script name");
		}

		std::string sourceFile(argv[1]);
		std::ifstream scriptFile(sourceFile, std::ios_base::binary);
		if (!scriptFile.is_open())
		{
			std::stringstream ss;
			ss << "Failed to open script file '" << sourceFile << "'";
			throw std::exception(ss.str().c_str());
		}

		std::string scriptToRun(argv[2]);
		int numberOfScripts = ReadInt(scriptFile);

		for (int script = 0 ; script < numberOfScripts ; ++script)
		{
			int nameLength = ReadInt(scriptFile);
			std::unique_ptr<char> apName(new char[nameLength]);
			scriptFile.read(apName.get(), nameLength);
			std::string scriptName(apName.get(), nameLength);

			int scriptLength = ReadInt(scriptFile);
			std::auto_ptr<char> scriptData(new char[scriptLength]);
			scriptFile.read(scriptData.get(), scriptLength);

			if (scriptName == scriptToRun)
			{
				MockInterpreter interpreter(scriptData.get());
				interpreter.Interpret();
			}
		}
	}
	catch (std::exception ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return -1;
	}

	return 0;
}


int ReadInt(std::ifstream& is)
{
	int v;
	is.read((char*)&v, sizeof(v));
	return v;
}


