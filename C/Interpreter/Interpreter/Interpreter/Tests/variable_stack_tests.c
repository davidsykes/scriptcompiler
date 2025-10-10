#include "test_rig.h"
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

void mock_fatal(const char* message)
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

void popping_off_the_bottom_generates_an_error(void* _context)
{
	VariableStackTestsContext* context = _context;
	VariableStack* stack = context->stack;
	fatal_fn = mock_fatal;

	stack->push_value(stack, context->value1);
	stack->pop_value(stack);
	stack->pop_value(stack);

	assert(strcmp(_error_message, "Variable stack underflow") == 0);
}

void pushing_over_the_top_generates_an_error(void* _context)
{
	VariableStackTestsContext* context = _context;
	VariableStack* stack = context->stack;

	for (int i = 0 ; i < 11 ; ++i)
	{
		stack->push_value(stack, context->value1);
	}

	assert(strcmp(_error_message, "Variable stack overflow") == 0);
}

void* set_up()
{
	VariableStackTestsContext* context = malloc(sizeof(*context));
	if (!context) abort();
	context->stack = variable_stack_create(10);
	context->value1 = variable_value_create(42);
	context->value2 = variable_value_create(1234);
	context->value3 = variable_value_create(99);
	_error_message = NULL;
	return context;
}

void tear_down(void* _context)
{
	VariableStackTestsContext* context = _context;
	variable_stack_delete(context->stack);
	variable_value_delete(context->value1);
	variable_value_delete(context->value2);
	variable_value_delete(context->value3);
	free(_context);
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