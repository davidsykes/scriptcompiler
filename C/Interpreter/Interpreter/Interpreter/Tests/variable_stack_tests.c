#include "..\variable_stack.h"

void run_variable_stack_tests()
{
	VariableStack* stack = variable_stack_create();

	variable_stack_delete(stack);
}