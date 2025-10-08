#include "assert.h"



void assert(int v)
{
	if (v==0)
	{
		*((char*)0) = 0;
	}
}