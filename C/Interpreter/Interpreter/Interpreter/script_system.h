#pragma once
#include "public/external_system.h"
#include "public/script_instance.h"

typedef struct ScriptSystem {
	int (*interpret)(struct ScriptSystem* script_system, ScriptInstance* script);
	void* system;
} ScriptSystem;



#ifdef __cplusplus
extern "C" {
#endif
	ScriptSystem* script_system_initialise(int stack_size, ExternalSystem* external_system);
#ifdef __cplusplus
}
#endif


