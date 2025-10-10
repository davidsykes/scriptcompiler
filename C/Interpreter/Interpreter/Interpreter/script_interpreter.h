#include "common_includes.h"



typedef struct ScriptInterpreterVTable {
	int (*interpret)(struct ScriptInterpreter* interpreter, const char *script);
} ScriptInterpreterVTable;


typedef struct ScriptInterpreter {
	struct ScriptInterpreterVTable* vtable;
	int value;
} ScriptInterpreter;


ScriptInterpreter* script_interpreter_create(int stack_size);
void script_interpreter_delete(ScriptInterpreter*);
