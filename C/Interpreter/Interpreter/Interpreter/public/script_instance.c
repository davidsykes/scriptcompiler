#include "../internal/xalloc.h"
#include "script_instance.h"
#include "variable_collection.h"



ScriptInstance* script_instance_create(ScriptCode* script)
{
	ScriptInstance* inst = xmalloc(sizeof(*inst));
	inst->script = script_code_navigator_create(script->script);
	inst->variable_stack = variable_stack_create();
	inst->local_variables = variable_collection_create();
	return inst;
}

void script_instance_delete(ScriptInstance* inst)
{
	script_code_navigator_delete(inst->script);
	variable_stack_delete(inst->variable_stack);
	variable_collection_delete(inst->local_variables);
	free(inst);
}

