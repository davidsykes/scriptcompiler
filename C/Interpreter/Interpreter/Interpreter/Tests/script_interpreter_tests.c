#include <string.h>
#include "test_rig.h"
#include "../internal/xalloc.h"
#include "../internal/script_interpreter.h"

#define MAX_SCRIPT_SIZE 1024

typedef struct ScriptInterpreterTestsContext {
	ScriptInterpreter* interpreter;
	VariableCollection* global_variables;
	char script_data[MAX_SCRIPT_SIZE];
	size_t script_pointer;
	ScriptCode* script_code;
	ScriptInstance* script_instance;
} ScriptInterpreterTestsContext;

static const char* last_called_routine;
static int fn_return_value = 0;

static void code_add_bytes(ScriptInterpreterTestsContext* context, const void* data, size_t size);
static void code_add_integer(ScriptInterpreterTestsContext* context, int value);
static void code_add_string(ScriptInterpreterTestsContext* context, const char* value);
static void code_add_fn_routine(ScriptInterpreterTestsContext* context, const char* name, int parameter_count);

static void FnRoutine(const char* name, VariableValue* parameters, int parameter_count, VariableValue* fn_return_variable)
{
	last_called_routine = name;
	variable_value_set_integer(fn_return_variable, fn_return_value);
}

static void call_fn_routine_with_no_parameters(ScriptInterpreterTestsContext* context)
{
	code_add_fn_routine(context, "FnRoutine", 0);
	code_add_integer(context, ENDSCRIPT);

	script_interpreter_interpret(
		context->interpreter,
		context->script_instance);

	assert(strcmp(last_called_routine, "FnRoutine") == 0);
}

static void call_fn_routine_return_value_is_pushed_on_to_the_stack(ScriptInterpreterTestsContext* context)
{
	code_add_fn_routine(context, "FnRoutine", 0);
	code_add_integer(context, POP_VARIABLE);
	code_add_string(context, "var");
	code_add_integer(context, ENDSCRIPT);

	fn_return_value = 42;
	script_interpreter_interpret(
		context->interpreter,
		context->script_instance);

	int set_value = variable_collection_get_variable(
		context->global_variables,
		"var")
		->integer;
	assert(set_value == 42);
}

static void when_fn_returns_0_script_continues(ScriptInterpreterTestsContext* context)
{
	code_add_fn_routine(context, "FnRoutine", 0);
	code_add_integer(context, DROPSKIPPAUSEREPEAT);
	code_add_integer(context, 999);
	code_add_fn_routine(context, "FnRoutine2", 0);
	code_add_integer(context, ENDSCRIPT);

	fn_return_value = 0;
	script_interpreter_interpret(
		context->interpreter,
		context->script_instance);

	assert(strcmp(last_called_routine, "FnRoutine2") == 0);
}

static void when_fn_returns_1_script_pauses_then_reruns(ScriptInterpreterTestsContext* context)
{
	ScriptInterpreter* interpreter = context->interpreter;

	const char* script_data =
		"\x16\0\0\0"		//callfnroutine
		"\0\0\0\0"			// 0 parameters
		"FnRoutine" "\0"
		"\x19\0\0\0"		// dropskippausenonzero
		"\xff\0\0\0"		// jump invalid
		"\x16\0\0\0"		//callfnroutine
		"\0\0\0\0"			// 0 parameters
		"FnRoutine2" "\0"
		"\x18\0\0\0";		// end script

	ScriptInstance* inst = script_instance_create(
		script_code_create(script_data));

	fn_return_value = 1;
	script_interpreter_interpret(
		interpreter,
		inst);
	assert(strcmp(last_called_routine, "FnRoutine") == 0);

	fn_return_value = 2;
	script_interpreter_interpret(
		interpreter,
		inst);
	assert(strcmp(last_called_routine, "FnRoutine") == 0);

	script_interpreter_interpret(
		interpreter,
		inst);
	assert(strcmp(last_called_routine, "FnRoutine2") == 0);
}

static void when_fn_returns_2_script_pauses(ScriptInterpreterTestsContext* context)
{
	ScriptInterpreter* interpreter = context->interpreter;

	const char* script_data =
		"\x16\0\0\0"		//callfnroutine
		"\0\0\0\0"			// 0 parameters
		"FnRoutine" "\0"
		"\x19\0\0\0"		// dropskippausenonzero
		"\xff\0\0\0"		// jump invalid
		"\x16\0\0\0"		//callfnroutine
		"\0\0\0\0"			// 0 parameters
		"FnRoutine2" "\0"
		"\x18\0\0\0";		// end script

	ScriptInstance* inst = script_instance_create(
		script_code_create(script_data));

	fn_return_value = 2;
	script_interpreter_interpret(
		interpreter,
		inst);
	assert(strcmp(last_called_routine, "FnRoutine") == 0);

	script_interpreter_interpret(
		interpreter,
		inst);
	assert(strcmp(last_called_routine, "FnRoutine2") == 0);
}


static void code_add_bytes(ScriptInterpreterTestsContext* context, const void* data, size_t size)
{
	memcpy(context->script_data + context->script_pointer, data, size);
	context->script_pointer += size;
}

static void code_add_integer(ScriptInterpreterTestsContext* context, int value)
{
	code_add_bytes(context, &value, sizeof(int));
}

static void code_add_string(ScriptInterpreterTestsContext* context, const char* value)
{
	code_add_bytes(context, value, strlen(value) + 1);
}

static void code_add_fn_routine(ScriptInterpreterTestsContext* context, const char* name, int parameter_count)
{
	code_add_integer(context, CALL_FN_ROUTINE);
	code_add_integer(context, parameter_count);
	code_add_string(context, name);
}


static void* script_interpreter_tests_set_up()
{
	ScriptInterpreterTestsContext* context = xmalloc(sizeof(*context));
	context->global_variables = variable_collection_create();
	context->interpreter = script_interpreter_create(
		context->global_variables,
		FnRoutine);
	context->script_pointer = 0;
	context->script_code = script_code_create(context->script_data);
	context->script_instance = script_instance_create(context->script_code);
	last_called_routine = 0;
	return context;
}

static void script_interpreter_tests_tear_down(void* _context)
{
	ScriptInterpreterTestsContext* context = _context;
	script_interpreter_delete(context->interpreter);
	variable_collection_delete(context->global_variables);
	script_instance_delete(context->script_instance);
	script_code_delete(context->script_code);
	free(_context);
}

void run_script_interpreter_tests()
{
	void (*tests[])(void* context) = {
		call_fn_routine_with_no_parameters,
		call_fn_routine_return_value_is_pushed_on_to_the_stack,
		when_fn_returns_0_script_continues,
		//when_fn_returns_1_script_pauses_then_reruns,
		//when_fn_returns_2_script_pauses,
		0
	};

	run_test_rig(
		script_interpreter_tests_set_up,
		script_interpreter_tests_tear_down,
		tests
	);
}