#include "common_includes.h"
#include "fatal.h"
#include <stdio.h>

void fatal(const char* message)
{
	if (fatal_fn)
	{
		fatal_fn(message);
	}
	else
	{
		fprintf(stderr, "Fatal error: %s\n", message);
		abort();
	}
}