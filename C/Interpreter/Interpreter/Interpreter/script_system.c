#include <assert.h>
#include "internal/xalloc.h"
#include "script_system.h"
#include "variable_stack.h"
#include "script_code_bock.h"
#include "script_interpreter.h"


typedef struct ScriptSystemImp {
	ScriptInterpreter* script_interpreter;
} ScriptSystemImp;



int interpret(struct ScriptSystem* script_system, const char* script)
{
	ScriptSystemImp* ssimp = script_system->system;
	ssimp->script_interpreter->vtable->interpret(ssimp->script_interpreter, script);
}

//static void* simalloc(size_t size)
//{
//	void* m = malloc(size);
//	if (!m) fatal("Memory allocation error.");
//	return m;
//}

ScriptSystem* script_system_initialise(
	int stack_size
)
{
	variable_stack_initialise();
	script_code_block_initialise();

	ScriptSystem* ss = xmalloc(sizeof(*ss));
	ss->interpret = &interpret;

	ScriptSystemImp* ssimp = xmalloc(sizeof(*ssimp));
	ssimp->script_interpreter = script_interpreter_create(stack_size);

	ss->system = ssimp;

	return ss;
}

