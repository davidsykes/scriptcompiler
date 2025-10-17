#include "test_rig.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "../internal/xalloc.h"
#include "../internal/variable_value.h"

typedef struct VariableValueTestsContext {
	VariableValue* value1;
} VariableValueTestsContext;

static void integer_values_can_be_set(VariableValueTestsContext* context)
{
	variable_value_set_integer(context->value1, 421);

	assert(variable_value_get_integer(context->value1) == 421);
}

static void string_values_can_be_set(VariableValueTestsContext* context)
{
	variable_value_set_string(context->value1, "421");

	const char* value = variable_value_get_string(context->value1);
	assert(strcmp(value, "421") == 0);
}

static void integers_are_null_strings(VariableValueTestsContext* context)
{
	variable_value_set_integer(context->value1, 421);

	assert(variable_value_get_string(context->value1) == 0);
}

static void strings_are_zero_integers(VariableValueTestsContext* context)
{
	variable_value_set_string(context->value1, "421");

	assert(variable_value_get_integer(context->value1) == 0);
}

static void* set_up()
{
	VariableValueTestsContext* context = xmalloc(sizeof(*context));
	context->value1 = variable_value_create();
	return context;
}

static void tear_down(void* _context)
{
	VariableValueTestsContext* context = _context;
	variable_value_delete(context->value1);
	free(_context);
}

void run_variable_value_tests()
{
	void (*tests[])(void* context) = {
		integer_values_can_be_set,
		string_values_can_be_set,
		integers_are_null_strings,
		strings_are_zero_integers,
		0
	};

	run_test_rig(
		set_up,
		tear_down,
		tests
	);
}