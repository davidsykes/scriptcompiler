#include <stddef.h>
#include "memory_tracker.h"
#include "fatal.h"

#define MAX_ALLOCATION_COUNT 1024

void* allocations[MAX_ALLOCATION_COUNT];
int allocation_counts2[MAX_ALLOCATION_COUNT];
const char* allocation_source[MAX_ALLOCATION_COUNT];
int allocation_index = 0;
int allocation_count = 0;

#define MEMORY_TRACKER_INDEX_BREAK -1

void track_memory(const char* origin, void* ptr)
{
	if (allocation_count == MEMORY_TRACKER_INDEX_BREAK)
	{
		allocation_count = allocation_count;
	}

	for (int i = 0; i < allocation_index; ++i)
	{
		if (allocations[i] == NULL)
		{
			allocations[i] = ptr;
			allocation_counts2[i] = allocation_count++;
			allocation_source[i] = origin;
			return;
		}
	}
	if (allocation_index < MAX_ALLOCATION_COUNT)
	{
		allocations[allocation_index] = ptr;
		allocation_source[allocation_index] = origin;
		allocation_counts2[allocation_index++] = allocation_count++;
	}
	else
	{
		fatal("Memory tracker allocation limit exceeded");
	}
}

void untrack_memory(void* ptr)
{
	for (int i = 0; i < allocation_index; ++i)
	{
		if (allocations[i] == ptr)
		{
			allocations[i] = NULL;
			allocation_counts2[i] = 0;
			allocation_source[i] = 0;
			return;
		}
	}
	fatal("Attempted to untrack untracked memory");
}

void track_memory_allocations()
{
	for (int i = 0; i < allocation_index; ++i)
	{
		if (allocations[i] != NULL)
		{
			void* p = allocations[i];
			int count = allocation_counts2[i];
			const char* origin = allocation_source[i];
			fatal("Memory leak detected");
		}
	}
}