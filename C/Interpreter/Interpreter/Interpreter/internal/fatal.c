#include <stdio.h>
#include <stdlib.h>
#include "fatal.h"

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