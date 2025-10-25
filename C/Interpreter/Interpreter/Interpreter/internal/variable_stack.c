#include <stdlib.h>
#include "xalloc.h"
#include "variable_stack.h"
#include "fatal.h"

#define VARIABLE_STACK_SIZE	10

typedef struct VariableStack {
	VariableValue values[10];
	int pointer;
} VariableStack;

void vs_push_value(VariableStack* stack, VariableValue* value)
{
	if (stack->pointer >= VARIABLE_STACK_SIZE)
	{
		fatal("Variable stack overflow");
		return;
	}
	variable_value_copy(&stack->values[stack->pointer], value);

	++stack->pointer;
}

void vs_pop_copy_value(VariableStack* stack, VariableValue* value)
{
	if (stack->pointer <= 0)
	{
		fatal("Variable stack underflow");
		return;
	}
	--stack->pointer;
	variable_value_copy(value, &stack->values[stack->pointer]);
}

VariableValue* vs_get_parameter_pointer(VariableStack* stack, int parameter_count)
{
	return &stack->values[stack->pointer - parameter_count];
}

VariableStack* variable_stack_create()
{
	VariableStack* stack = xmalloc(MEM_VARIABLE_STACK, sizeof(*stack));
	stack->pointer = 0;

	return stack;
}

void variable_stack_delete(VariableStack* stack)
{
	xfree(stack);
}