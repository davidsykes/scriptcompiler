#include <assert.h>
#include "internal/xalloc.h"
#include "script_system.h"
#include "internal/variable_stack.h"
#include "internal/script_code_bock.h"
#include "internal/script_interpreter.h"


typedef struct ScriptSystemImp {
	ScriptInterpreter* script_interpreter;
} ScriptSystemImp;



int interpret(struct ScriptSystem* script_system, const char* script)
{
	ScriptSystemImp* ssimp = script_system->system;
	int r = ssimp->script_interpreter->vtable->interpret(ssimp->script_interpreter, script);
	return r;
}

ScriptSystem* script_system_initialise(int stack_size, ExternalSystem* external_system)
{
	variable_stack_initialise();

	ScriptSystem* ss = xmalloc(sizeof(*ss));
	ss->interpret = &interpret;

	ScriptSystemImp* ssimp = xmalloc(sizeof(*ssimp));
	ssimp->script_interpreter = script_interpreter_create(stack_size, external_system);

	ss->system = ssimp;

	return ss;
}

