// (c) David Sykes 2013
// One more time, for the kids!

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#include "script_system.h"
#include "public/external_system.h"
#include "public/script_code.h"
#include "public/script_instance.h"

#ifdef __cplusplus
extern "C" {
#endif
int main_c(const char* scriptData);
void run_script_interpreter_tests();
#ifdef __cplusplus
}
#endif
int	ReadInt(std::ifstream& is);

int main(int argc, char* argv[])
{
	ExternalSystem* external_system = external_system_create();

	ScriptSystem* script_system = script_system_initialise(
		10,
		external_system
	);
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
				const char* script = scriptData.get();
				ScriptCode* code = script_code_create(script);
				ScriptInstance* inst = script_instance_create(code);

				int result = script_system
					->interpret(script_system, inst);
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


