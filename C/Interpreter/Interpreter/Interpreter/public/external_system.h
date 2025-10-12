#pragma once


typedef struct ExternalSystem {
	void (*set_global_variable)(const char* name, int value);
	void* system;
} ExternalSystem;

#ifdef __cplusplus
extern "C" {
#endif
	ExternalSystem* external_system_create(void);
#ifdef __cplusplus
}
#endif

