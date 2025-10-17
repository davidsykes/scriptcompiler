#pragma once



typedef struct VariableValue VariableValue;
typedef struct ScriptCode ScriptCode;
typedef struct ScriptInstance ScriptInstance;
typedef struct VariableCollection VariableCollection;
typedef struct ScriptInterpreter ScriptInterpreter;

typedef VariableValue* (*FN_ROUTINE)(const char* name);

VariableValue* variable_value_create_integer(int value);
VariableValue* variable_value_create_tring(const char* value);
ScriptCode* script_code_create(const char* script);
ScriptInstance* script_instance_create(ScriptCode* script);

VariableCollection* variable_collection_create(void);
ScriptInterpreter* script_interpreter_create(
	VariableCollection* gobal_variables,
	FN_ROUTINE fn_routine);
int script_interpreter_interpret(struct ScriptInterpreter* interpreter, ScriptInstance* script);

