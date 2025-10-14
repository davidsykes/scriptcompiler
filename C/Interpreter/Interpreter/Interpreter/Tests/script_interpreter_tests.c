#include "test_rig.h"
#include "../internal/xalloc.h"
#include "../internal/script_interpreter.h"

typedef struct ScriptInterpreterTestsContext {
	ScriptInterpreter* interpreter;
	VariableCollection* global_variables;
} ScriptInterpreterTestsContext;


static void call_fn_routine_with_no_parameters(ScriptInterpreterTestsContext* context)
{
	ScriptInterpreter* interpreter = context->interpreter;

	assert(0);
}

void* script_interpreter_tests_set_up()
{
	ScriptInterpreterTestsContext* context = xmalloc(sizeof(*context));
	context->global_variables = variable_collection_create();
	context->interpreter = script_interpreter_create(context->global_variables);
	return context;
}

void script_interpreter_tests_tear_down(void* _context)
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