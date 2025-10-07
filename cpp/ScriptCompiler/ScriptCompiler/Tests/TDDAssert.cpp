
#include "TDDAssert.h"

void AssertTrue(bool flag)
{
	if (!flag)
		*((char *)0) = 0;
}

void AssertFalse(bool flag)
{
	AssertTrue(!flag);
}

#if 0

void AssertEqual(const std::string a, const std::string b)
{
	AssertTrue(a == b);
}

void AssertEqual(int a, int b)
{
	AssertTrue(a == b);
}

#endif

