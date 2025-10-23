#include "public/script_interpreter_interface.h"
#include "internal/memory_tracker.h"

void run_all_tests();

static void FnRoutine(const char* fn_routine_name, VariableValue** parameters, int parameter_count, VariableValue* return_value)
{
	variable_value_set_integer(return_value, 0);
}

int main_c(const char* scriptData)
{
	run_all_tests();

	ScriptInstance* inst = script_instance_create(scriptData);
	VariableCollection* globals = variable_collection_create();
	ScriptInterpreter* interpreter = script_interpreter_create(globals, FnRoutine);

	int result = 0;
	do
	{
		result = script_interpreter_interpret(interpreter, inst);
	} while (!result);

	track_memory_allocations();

	return result;
}