#include "variable_stack.h"
#include "script_code_bock.h"



void* script_system_initialise()
{
	variable_stack_initialise();
	script_code_block_initialise();
}

