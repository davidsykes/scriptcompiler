
#include <string>

void Assert(bool v /* =false */)
{
	if (!v)
		*((char*)0) = 0;
}

void AssertEqual(int a, int b)
{
	if (a != b)
		*((char*)0) = 0;
}


void AssertEqual(const char* a, const std::string& b)
{
	if (strcmp(a, b.c_str()) != 0)
		*((char*)0) = 0;
}

