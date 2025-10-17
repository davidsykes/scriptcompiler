#include "public/script_interpreter_interface.h"

void run_all_tests();

static VariableValue* FnRoutine(const char* name)
{
	return variable_value_create_integer(0);
}

int main_c(const char* scriptData)
{
	run_all_tests();

	ScriptCode* script_code = script_code_create(scriptData);
	ScriptInstance* inst = script_instance_create(script_code);
	VariableCollection* globals = variable_collection_create();
	ScriptInterpreter* interpreter = script_interpreter_create(globals, FnRoutine);

	int result = 0;
	do
	{
		result = script_interpreter_interpret(interpreter, inst);
	} while (!result);

	return result;
}