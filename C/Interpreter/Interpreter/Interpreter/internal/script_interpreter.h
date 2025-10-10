#pragma once



typedef struct ScriptInterpreterVTable {
	int (*interpret)(struct ScriptInterpreter* interpreter, const char *script);
} ScriptInterpreterVTable;


typedef struct ScriptInterpreter {
	struct ScriptInterpreterVTable* vtable;
	int stack_size;
} ScriptInterpreter;


ScriptInterpreter* script_interpreter_create(int stack_size);
void script_interpreter_delete(ScriptInterpreter*);
