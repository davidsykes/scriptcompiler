#include "public/script_interpreter_interface.h"

void run_all_tests();

static VariableValue* FnRoutine(const char* name)
{
	return variable_value_create_integer(0);
}

int main_c(const char* scriptData)
{
	run_all_tests();

	ScriptCode* code = script_code_create(scriptData);
	ScriptInstance* inst = script_instance_create(code);
	VariableCollection* globals = variable_collection_create(100);
	ScriptInterpreter* interpreter = script_interpreter_create(globals, FnRoutine);

	int result = 0;
	do
	{
		result = script_interpreter_interpret(interpreter, inst);
	} while (!result);

	return result;
}