#include "public/script_code.h"
#include "public/script_instance.h"
#include "public/variable_collection.h"
#include "internal/script_interpreter.h"

run_all_tests();



static VariableValue* FnRoutine(const char* name)
{
	return variable_value_create(0);
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
		script_interpreter_interpret(interpreter, inst);
	} while (!result);

	return result;
}