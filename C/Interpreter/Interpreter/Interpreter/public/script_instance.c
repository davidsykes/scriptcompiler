#include "../internal/xalloc.h"
#include "script_instance.h"




ScriptInstance* script_instance_create(ScriptCode* script)
{
	ScriptInstance* inst = xmalloc(sizeof(*inst));
	inst->script = script_code_navigator_create(script->script);
	inst->variable_stack = variable_stack_create();
	return inst;
}

void script_instance_delete(ScriptInstance* inst)
{
	variable_stack_delete(inst->variable_stack);
	free(inst);
}

