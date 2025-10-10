#include "internal/xalloc.h"
#include "script_interpreter.h"

static int interpret(struct ScriptInterpreter* interpreter, const char* script)
{

}

static const ScriptInterpreterVTable _scriptCodeBlockVTable = {
	.interpret = &interpret
};

ScriptInterpreter* script_interpreter_create(int stack_size)
{
	ScriptInterpreter* si = xmalloc(sizeof(*si));

	si->vtable = &_scriptCodeBlockVTable;
	//si->script_data = scriptData;
	//si->script_pointer = 0;

	return si;
}