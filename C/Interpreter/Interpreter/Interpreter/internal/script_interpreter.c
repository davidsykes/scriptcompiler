#include "xalloc.h"
#include "script_interpreter.h"
#include "script_instance.h"


#define ERR_INVALID_OPCODE 1

#define pushintvalue 1
/*
	pushparam = 2
pushstring = 3
pushvariable = 4
popvariable = 5
jfalse = 6
jtrue = 7
jall = 8
add = 9
subtract = 10
multiply = 11
devide = 12
negate = 13
logicalnot = 14
lt = 15
gt = 16
lte = 17
gte = 18
equals = 19
logicaland = 20
logicalor = 21
callfnroutine = 22
dropstackvalue = 23
endscript = 24
*/

static int interpret(struct ScriptInterpreter* interpreter, const char* script)
{
	ScriptInstance* inst = script_instance_create(script, interpreter->stack_size);
	ScriptCodeBlock* code = inst->code_block;
	VariableStack* variable_stack = inst->variable_stack;

	while (1)
	{
		int opcode = code->_vtable->fetch_int(code);

		switch (opcode)
		{
		case pushintvalue:
		{
			int intvalue = code->_vtable->fetch_int(code);
			VariableValue* value = variable_value_create(intvalue);
			variable_stack->push_value(variable_stack, value);
		}
			break;

		default:
			script_instance_delete(inst);
			return ERR_INVALID_OPCODE;
		}
	}
}

static const ScriptInterpreterVTable _scriptCodeBlockVTable = {
	.interpret = &interpret
};

ScriptInterpreter* script_interpreter_create(int stack_size)
{
	ScriptInterpreter* si = xmalloc(sizeof(*si));

	si->vtable = &_scriptCodeBlockVTable;
	si->stack_size = stack_size;

	return si;
}