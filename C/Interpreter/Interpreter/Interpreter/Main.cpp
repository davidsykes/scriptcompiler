// (c) David Sykes 2013
// One more time, for the kids!

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

#ifdef __cplusplus
extern "C" {
#endif
#include <vector>
void run_all_tests();
int run_script(const char* scriptData, const char* script_name);
#ifdef __cplusplus
}
#endif

static std::vector<std::byte> LoadEntireFile(const char* filePath);

int main(int argc, char* argv[])
{
	run_all_tests();

	try
	{
		if (argc != 3)
		{
			throw std::exception("Missing script file or script name");
		}
		const char* scriptFileName = argv[1];
		const char* scriptName = argv[2];


		std::vector<std::byte> scriptData = LoadEntireFile(scriptFileName);

		int result = run_script((const char*)scriptData.data(), scriptName);
	}
	catch (std::exception ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
		return -1;
	}

	return 0;
}


static std::vector<std::byte> LoadEntireFile(const char* filePath)
{
	std::ifstream file(filePath, std::ifstream::binary);

	if (file)
	{

		file.seekg(0, file.end);
		std::streampos end_pos = file.tellg();
		file.seekg(0, file.beg);
		std::vector<std::byte> buf(static_cast<size_t>(end_pos));

		if (end_pos > 0 && file.read(reinterpret_cast<char*>(buf.data()), end_pos))
		{
			return buf;
		}
	}
	throw std::exception("Error loading script file");
}