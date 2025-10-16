#pragma once
#include "script_instance.h"
#include "variable_collection.h"
#include "fn_routines.h"

typedef struct ScriptInterpreter ScriptInterpreter;


ScriptInterpreter* script_interpreter_create(
	VariableCollection* gobal_variables,
	FN_ROUTINE fn_routine);
void script_interpreter_delete(ScriptInterpreter*);

int script_interpreter_interpret(struct ScriptInterpreter* interpreter, ScriptInstance* script);
