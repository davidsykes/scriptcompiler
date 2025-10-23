#pragma once

typedef struct VariableValue VariableValue;
typedef struct ScriptInstance ScriptInstance;
typedef struct VariableCollection VariableCollection;
typedef struct ScriptInterpreter ScriptInterpreter;

typedef void (*FN_ROUTINE)(const char* name, VariableValue** parameters, int parameter_count, VariableValue* fn_return_value);

void variable_value_set_integer(VariableValue* value, int integer);
ScriptInstance* script_instance_create(const char* script);

VariableCollection* variable_collection_create(void);
ScriptInterpreter* script_interpreter_create(
	VariableCollection* gobal_variables,
	FN_ROUTINE fn_routine);
int script_interpreter_interpret(struct ScriptInterpreter* interpreter, ScriptInstance* script);

