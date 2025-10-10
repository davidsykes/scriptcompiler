#pragma once
#include "script_code_bock.h"
#include "variable_stack.h"


typedef struct ScriptInstance ScriptInstance;

//typedef struct ScriptCodeBlockVTable {
//	int (*fetch_int)(struct ScriptCodeBlock* self);
//} ScriptCodeBlockVTable;


typedef struct ScriptInstance {
	//struct ScriptCodeBlockVTable* _vtable;
	ScriptCodeBlock* code_block;
	VariableStack* variable_stack;
} ScriptInstance;


ScriptInstance* script_instance_create(const char* scriptData, int stack_size);
void script_instance_delete(ScriptInstance*);