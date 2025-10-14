#include <string.h>
#include "test_rig.h"
#include "../internal/xalloc.h"
#include "../internal/script_interpreter.h"

typedef struct ScriptInterpreterTestsContext {
	ScriptInterpreter* interpreter;
	VariableCollection* global_variables;
} ScriptInterpreterTestsContext;

static const char* called_routine;

static VariableValue* FnRoutine(const char* name)
{
	called_routine = name;
	return variable_value_create(0);
}


static void call_fn_routine_with_no_parameters(ScriptInterpreterTestsContext* context)
{
	ScriptInterpreter* interpreter = context->interpreter;

	const char* script_data =
		"\x16\0\0\0" //callfnroutine
		"\0\0\0\0"
		"FnRoutine" "\0"
		"\x18\0\0\0";

	ScriptInstance* inst = script_instance_create(
		script_code_create(script_data));

	int result = script_interpreter_interpret(
		interpreter,
		inst);

	assert(strcmp(called_routine, "FnRoutine") == 0);
}

static void* script_interpreter_tests_set_up()
{
	ScriptInterpreterTestsContext* context = xmalloc(sizeof(*context));
	context->global_variables = variable_collection_create();
	context->interpreter = script_interpreter_create(
		context->global_variables,
		FnRoutine);
	called_routine = 0;
	return context;
}

static void script_interpreter_tests_tear_down(void* _context)
{
	ScriptInterpreterTestsContext* context = _context;
	script_interpreter_delete(context->interpreter);
	variable_collection_delete(context->global_variables);
	free(_context);
}

void run_script_interpreter_tests()
{
	void (*tests[])(void* context) = {
		call_fn_routine_with_no_parameters,
		0
	};

	run_test_rig(
		script_interpreter_tests_set_up,
		script_interpreter_tests_tear_down,
		tests
	);
}