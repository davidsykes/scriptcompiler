#include "test_rig.h"
#include "../internal/xalloc.h"
#include "..\internal/variable_stack.h"
#include <string.h>
#include "..\internal/fatal.h"

typedef struct VariableStackTestsContext {
	VariableStack* stack;
	VariableValue* value1;
	VariableValue* value2;
	VariableValue* value3;
} VariableStackTestsContext;

const char* _error_message;

static void mock_fatal(const char* message)
{
	_error_message = message;
}

static void values_can_be_pushed_and_popped(void* _context)
{
	VariableStackTestsContext* context = _context;
	VariableStack* stack = context->stack;

	stack->push_value(stack, context->value1);
	stack->push_value(stack, context->value2);
	stack->push_value(stack, context->value3);

	assert(stack->pop_value(stack) == context->value3);
	assert(stack->pop_value(stack) == context->value2);
	assert(stack->pop_value(stack) == context->value1);
}

static void popping_off_the_bottom_generates_an_error(void* _context)
{
	VariableStackTestsContext* context = _context;
	VariableStack* stack = context->stack;
	fatal_fn = mock_fatal;

	stack->push_value(stack, context->value1);
	stack->pop_value(stack);
	stack->pop_value(stack);

	assert(strcmp(_error_message, "Variable stack underflow") == 0);
}

static void pushing_over_the_top_generates_an_error(void* _context)
{
	VariableStackTestsContext* context = _context;
	VariableStack* stack = context->stack;
	fatal_fn = mock_fatal;

	for (int i = 0 ; i < 11 ; ++i)
	{
		stack->push_value(stack, context->value1);
	}

	assert(strcmp(_error_message, "Variable stack overflow") == 0);
}

static void* set_up()
{
	VariableStackTestsContext* context = xmalloc(sizeof(*context));
	context->stack = variable_stack_create();
	context->value1 = variable_value_create_integer(42);
	context->value2 = variable_value_create_integer(1234);
	context->value3 = variable_value_create_integer(99);
	_error_message = NULL;
	return context;
}

static void tear_down(void* _context)
{
	VariableStackTestsContext* context = _context;
	variable_stack_delete(context->stack);
	variable_value_delete(context->value1);
	variable_value_delete(context->value2);
	variable_value_delete(context->value3);
	free(_context);
	fatal_fn = 0;
}

void run_variable_stack_tests()
{
	void (*tests[])(void* context) = {
		values_can_be_pushed_and_popped,
		popping_off_the_bottom_generates_an_error,
		pushing_over_the_top_generates_an_error,
		0
	};

	run_test_rig(
		set_up,
		tear_down,
		tests
	);
}