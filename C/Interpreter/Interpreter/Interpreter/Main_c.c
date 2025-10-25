#include <stdlib.h>
#include <string.h>
#include "public/script_interpreter_interface.h"
#include "internal/memory_tracker.h"

static void FnRoutine(const char* fn_routine_name, VariableValue** parameters, int parameter_count, VariableValue* return_value)
{
	variable_value_set_integer(return_value, 0);
}

const char* find_script_data(const char* scriptData, const char* script_name);

int run_script(const char* scriptData, const char* script_name)
{
	const char* script_data = find_script_data(scriptData, script_name);

	ScriptInstance* inst = script_instance_create(script_data);
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


const char* find_script_data(const char* scriptData, const char* script_name)
{
	size_t script_name_length = strlen(script_name);
	const char* ptr = scriptData;
	int script_count = *((int*)ptr);
	ptr += sizeof(int);

	for (int script = 0; script < script_count; ++script)
	{
		int name_len = *((int*)ptr);
		ptr += sizeof(int);
		const char* name_ptr = ptr;
		ptr += name_len;
		int script_length = *((int*)ptr);
		ptr += sizeof(int);
		const char* script_ptr = ptr;
		ptr += script_length;

		if (name_len == script_name_length && strncmp(name_ptr, script_name, script_name_length) == 0)
		{
			return script_ptr;
		}
	}
	return NULL;
}


