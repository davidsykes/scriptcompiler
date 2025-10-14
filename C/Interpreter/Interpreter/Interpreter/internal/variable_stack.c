#include <stdlib.h>
#include "xalloc.h"
#include "variable_stack.h"
#include "fatal.h"

#define VARIABLE_STACK_SIZE	10

static void push_value(VariableStack* stack, VariableValue* value)
{
	if (stack->pointer >= VARIABLE_STACK_SIZE)
	{
		fatal("Variable stack overflow");
		return;
	}
	stack->values[stack->pointer] = value;
	++stack->pointer;
}

static VariableValue* pop_value(VariableStack* stack)
{
	if (stack->pointer <= 0)
	{
		fatal("Variable stack underflow");
		return NULL;
	}
	--stack->pointer;
	return stack->values[stack->pointer];
}

VariableStack* variable_stack_create()
{
	VariableStack* stack = xmalloc(sizeof(*stack));
	if (stack)
	{
		stack->push_value = push_value;
		stack->pop_value = pop_value;
		stack->values = xmalloc(VARIABLE_STACK_SIZE * sizeof(VariableValue*));
		stack->pointer = 0;
	}
	return stack;
}

void variable_stack_delete(VariableStack* stack)
{
	free(stack);
}