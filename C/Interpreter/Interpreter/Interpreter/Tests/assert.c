#include "assert.h"



void assert_(int v)
{
	if (v==0)
	{
		*((char*)0) = 0;
	}
}