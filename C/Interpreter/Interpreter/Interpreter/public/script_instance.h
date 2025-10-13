#pragma once
#include "script_code.h"
#include "../internal/script_code_navigator.h"
#include "../internal/variable_stack.h"

typedef struct ScriptInstance {
	ScriptCodeNavigator* script;
	VariableStack* variable_stack;
} ScriptInstance;

#ifdef __cplusplus
extern "C" {
#endif
	ScriptInstance* script_instance_create(ScriptCode* script);
	void script_instance_delete(ScriptInstance*);
#ifdef __cplusplus
}
#endif

