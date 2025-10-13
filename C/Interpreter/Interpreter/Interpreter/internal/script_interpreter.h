#pragma once
#include "../public/external_system.h"
#include "../public/script_instance.h"


typedef struct ScriptInterpreterVTable {
	int (*interpret)(struct ScriptInterpreter* interpreter, ScriptInstance* script);
} ScriptInterpreterVTable;


typedef struct ScriptInterpreter {
	const ScriptInterpreterVTable* vtable;
	int stack_size;
	ExternalSystem* external_system;
} ScriptInterpreter;


ScriptInterpreter* script_interpreter_create(int stack_size, ExternalSystem* external_system);
void script_interpreter_delete(ScriptInterpreter*);
