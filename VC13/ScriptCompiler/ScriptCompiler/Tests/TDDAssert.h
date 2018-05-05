

#include <string>

void AssertTrue(bool flag);
void AssertFalse(bool flag);

template <class myType1, class myType2>
void AssertEqual(myType1 a, myType2 b)
{
	AssertTrue(a == b);
}


#if 0
void AssertEqual(const std::string& a, const std::string& b);
void AssertEqual(const std::string& a, const char * b);
void AssertEqual(int a, int b);


#endif

