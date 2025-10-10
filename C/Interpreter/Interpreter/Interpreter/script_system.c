#include "script_system.h"
#include "variable_stack.h"
#include "script_code_bock.h"

int interpret(struct ScriptSystem* script_system, const char* script)
{

}

ScriptSystem* script_system_initialise()
{
	variable_stack_initialise();
	script_code_block_initialise();

	ScriptSystem* ss = (ScriptSystem*)malloc(sizeof(ScriptSystem));
	ss->interpret = &interpret;
	return ss;
}

