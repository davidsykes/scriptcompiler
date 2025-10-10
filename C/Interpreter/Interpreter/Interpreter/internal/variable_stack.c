#include <stdlib.h>
#include "xalloc.h"
#include "variable_stack.h"
#include "fatal.h"

void variable_stack_initialise()
{

}

static void push_value(VariableStack* stack, VariableValue* value)
{
	if (stack->pointer >= stack->stack_size)
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

VariableStack* variable_stack_create(int stack_size)
{
	VariableStack* stack = xmalloc(sizeof(*stack));
	if (stack)
	{
		stack->push_value = push_value;
		stack->pop_value = pop_value;
		stack->values = xmalloc(stack_size * sizeof(VariableValue*));
		stack->pointer = 0;
		stack->stack_size = stack_size;
	}
	return stack;
}

void variable_stack_delete(VariableStack* stack)
{
	free(stack);
}