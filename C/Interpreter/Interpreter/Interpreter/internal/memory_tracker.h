#pragma once

#define MEMORY_TRACKER_ENABLED 0


void track_memory(const char* origin, void* ptr);
void untrack_memory(void* ptr);
void track_memory_allocations();
