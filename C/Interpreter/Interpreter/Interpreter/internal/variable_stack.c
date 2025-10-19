#include <stdlib.h>
#include "xalloc.h"
#include "variable_stack.h"
#include "fatal.h"

#define VARIABLE_STACK_SIZE	10

typedef struct VariableStack {
	VariableValue** values;
	int pointer;
} VariableStack;

void vs_push_value(VariableStack* stack, VariableValue* value)
{
	if (stack->pointer >= VARIABLE_STACK_SIZE)
	{
		fatal("Variable stack overflow");
		return;
	}
	stack->values[stack->pointer] = value;
	++stack->pointer;
}

VariableValue* vs_pop_value(VariableStack* stack)
{
	if (stack->pointer <= 0)
	{
		fatal("Variable stack underflow");
		return NULL;
	}
	--stack->pointer;
	return stack->values[stack->pointer];
}


VariableValue** vs_get_parameter_pointer(VariableStack* stack, int parameter_count)
{
	return stack->values + (stack->pointer - parameter_count);
}

VariableStack* variable_stack_create()
{
	VariableStack* stack = xmalloc(sizeof(*stack));
	stack->values = xmalloc(VARIABLE_STACK_SIZE * sizeof(VariableValue*));
	stack->pointer = 0;

	return stack;
}

void variable_stack_delete(VariableStack* stack)
{
	free(stack->values);
	free(stack);
}