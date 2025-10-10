#include "script_interpreter.h"



//static const ScriptInterpreterVTable _scriptCodeBlockVTable = {
//	.say_hello = greet,
//	.add = sum
//};

ScriptInterpreter* script_interpreter_create(int stack_size)
{
	ScriptInterpreter* si = (ScriptInterpreter*)malloc(sizeof(ScriptInterpreter));
	if (si == NULL) {
		return NULL;
	}

	//si->_vtable = &_scriptCodeBlockVTable;
	//si->script_data = scriptData;
	//si->script_pointer = 0;

	return si;
}