#include "../internal/xalloc.h"
#include "script_instance.h"
#include "variable_collection.h"



ScriptInstance* script_instance_create(const char* script)
{
	ScriptInstance* inst = xmalloc(MEM_SCRIPT_INSTANCE, sizeof(*inst));
	inst->script = script_code_navigator_create(script);
	inst->variable_stack = variable_stack_create();
	inst->local_variables = variable_collection_create();
	inst->fn_return_value = variable_value_create();
	return inst;
}

void script_instance_delete(ScriptInstance* inst)
{
	script_code_navigator_delete(inst->script);
	variable_stack_delete(inst->variable_stack);
	variable_collection_delete(inst->local_variables);
	free(inst);
}

