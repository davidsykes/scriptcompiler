#pragma once
#include "../public/script_instance.h"
#include "../public/variable_collection.h"

typedef struct ScriptInterpreter ScriptInterpreter;


ScriptInterpreter* script_interpreter_create(VariableCollection* gobal_variables);
void script_interpreter_delete(ScriptInterpreter*);

int script_interpreter_interpret(struct ScriptInterpreter* interpreter, ScriptInstance* script);