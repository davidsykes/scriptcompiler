#include "xalloc.h"
#include "script_interpreter.h"
#include "../public/script_instance.h"


#define ERR_INVALID_OPCODE 1

#define pushintvalue 1
/*
	pushparam = 2
pushstring = 3
pushvariable = 4
*/
#define popvariable 5
/*
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
#define PAUSE				26
#define POP_LOCAL_VARIABLE	28

static int interpret(struct ScriptInterpreter* interpreter, ScriptInstance* script)
{
	ScriptCodeNavigator* code = script->script;
	VariableStack* variable_stack = script->variable_stack;

	while (1)
	{
		int opcode = code->fn->fetch_int(code);

		switch (opcode)
		{
		case pushintvalue:
		{
			int intvalue = code->fn->fetch_int(code);
			VariableValue* value = variable_value_create(intvalue);
			variable_stack->push_value(variable_stack, value);
		}
		break;

		case popvariable:
		{
			const char* varname = (const char*)code->fn->fetch_string(code);
			VariableValue* value = variable_stack->pop_value(variable_stack);
			interpreter->external_system->set_global_variable(varname, value->value);
		}
		break;

		case PAUSE:
			return 0;
			break;

		case POP_LOCAL_VARIABLE:
		{
			const char* varname = (const char*)code->fn->fetch_string(code);
			VariableValue* value = variable_stack->pop_value(variable_stack);
			interpreter->external_system->set_local_variable(varname, value->value);
		}
		break;

		default:
			fatal("Invalid opcode");
			return ERR_INVALID_OPCODE;
		}
	}
}

static const ScriptInterpreterVTable _scriptCodeBlockFnTable = {
	.interpret = &interpret
};

ScriptInterpreter* script_interpreter_create(int stack_size, ExternalSystem* external_system)
{
	ScriptInterpreter* si = xmalloc(sizeof(*si));

	si->vtable = &_scriptCodeBlockFnTable;
	si->stack_size = stack_size;
	si->external_system = external_system;

	return si;
}