// (c) David Sykes 2013
// One more time, for the kids!

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#ifdef __cplusplus
extern "C" {
#endif
int main_c(const char* scriptData);
void run_script_interpreter_tests();
void* script_system_initialise();
#ifdef __cplusplus
}
#endif
int	ReadInt(std::ifstream& is);

int main(int argc, char* argv[])
{
	void* script_system = script_system_initialise();
	run_script_interpreter_tests();


	try
	{
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
			std::unique_ptr<char[]> scriptData(new char[scriptLength]);
			scriptFile.read(scriptData.get(), scriptLength);

			if (scriptName == scriptToRun)
			{
				int result = main_c(scriptData.get());
				if (result != 0)
				{
					std::cerr << "Script returned error code " << result << std::endl;
				}
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


