#include "xalloc.h"
#include "script_instance.h"

ScriptInstance* script_instance_create(const char* scriptData, int stack_size)
{
	ScriptInstance* i = xmalloc(sizeof(*i));

	i->code_block = script_code_block_create(scriptData);
	i->variable_stack = variable_stack_create(stack_size);

	return i;
}

void script_instance_delete(ScriptInstance* code)
{
	script_code_block_delete(code->code_block);
	variable_stack_delete(code->variable_stack);
	free(code);
}

