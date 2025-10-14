#include "xalloc.h"
#include "script_interpreter.h"
#include "../public/script_instance.h"


typedef struct ScriptInterpreter {
	VariableCollection* global_variables;
} ScriptInterpreter;


#define ERR_INVALID_OPCODE 1

#define PUSH_INT_VALUE 1
/*
	pushparam = 2
pushstring = 3
pushvariable = 4
*/
#define POP_VARIABLE 5
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
*/
#define CALL_FN_ROUTINE		22
/*
dropstackvalue = 23
endscript = 24
*/
#define PAUSE				26
#define POP_LOCAL_VARIABLE	28

int script_interpreter_interpret(struct ScriptInterpreter* interpreter, ScriptInstance* script)
{
	ScriptCodeNavigator* code = script->script;
	VariableStack* variable_stack = script->variable_stack;

	while (1)
	{
		int opcode = scn_fetch_int(code);

		switch (opcode)
		{
		case PUSH_INT_VALUE:
		{
			int intvalue = scn_fetch_int(code);
			VariableValue* value = variable_value_create(intvalue);
			variable_stack->push_value(variable_stack, value);
		}
		break;

		case POP_VARIABLE:
		{
			const char* varname = scn_fetch_string(code);
			VariableValue* value = variable_stack->pop_value(variable_stack);
			variable_collection_set_variable(
				interpreter->global_variables, varname, value);
		}
		break;

		case CALL_FN_ROUTINE:
			break;

		case PAUSE:
			return 0;
			break;

		case POP_LOCAL_VARIABLE:
		{
			const char* varname = scn_fetch_string(code);
			VariableValue* value = variable_stack->pop_value(variable_stack);
			variable_collection_set_variable(
				script->local_variables,
				varname,
				value
			);
		}
		break;

		default:
			fatal("Invalid opcode");
			return ERR_INVALID_OPCODE;
		}
	}
}

ScriptInterpreter* script_interpreter_create(VariableCollection* gobal_variables)
{
	ScriptInterpreter* si = xmalloc(sizeof(*si));

	si->global_variables = gobal_variables;

	return si;
}

void script_interpreter_delete(ScriptInterpreter* si)
{
	free(si);
}