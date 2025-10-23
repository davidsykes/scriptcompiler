#pragma once
#include "../internal/script_code_navigator.h"
#include "../internal/variable_stack.h"
#include "variable_collection.h"

typedef struct ScriptInstance {
	ScriptCodeNavigator* script;
	VariableStack* variable_stack;
	VariableCollection* local_variables;
	VariableValue* fn_return_value;
} ScriptInstance;

ScriptInstance* script_instance_create(const char* script);
void script_instance_delete(ScriptInstance*);
