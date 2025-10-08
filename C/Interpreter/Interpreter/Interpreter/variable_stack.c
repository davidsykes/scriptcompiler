#include "variable_stack.h"



VariableStack* variable_stack_create()
{
	VariableStack* code = (VariableStack*)malloc(sizeof(VariableStack));
	return code;
}

void variable_stack_delete(VariableStack* stack)
{
	free(stack);
}