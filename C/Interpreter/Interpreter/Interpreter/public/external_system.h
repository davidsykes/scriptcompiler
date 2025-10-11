#pragma once


typedef struct ExternalSystem {
	int (*set_global_variable)(const char* name, int value);
	void* system;
} ExternalSystem;

