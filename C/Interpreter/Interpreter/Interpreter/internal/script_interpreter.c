#include "xalloc.h"
#include "script_interpreter.h"
#include "script_instance.h"


typedef struct ScriptInterpreter {
	VariableCollection* global_variables;
	FN_ROUTINE fn_routine;
} ScriptInterpreter;


int script_interpreter_interpret(
	struct ScriptInterpreter* interpreter,
	ScriptInstance* script)
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
			VariableValue* value = variable_value_create_integer(intvalue);
			variable_stack->push_value(variable_stack, value);
		}
		break;

		case PUSH_STRING_VALUE:
		{
			const char* string_value = scn_fetch_string(code);
			VariableValue* value = variable_value_create_string(string_value);
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
		{
			scn_fetch_int(code);
			const char* fnname = scn_fetch_string(code);
			interpreter->fn_routine(fnname, 0, 0, script->fn_return_value);
			VariableValue* value_copy = variable_value_create_copy(script->fn_return_value);
			variable_stack->push_value(variable_stack, value_copy);
		}
		break;

		case ENDSCRIPT:
			return 1;

		case DROPSKIPPAUSEREPEAT:
		{
			int jump = scn_fetch_int(code);
			VariableValue* value = variable_stack->pop_value(variable_stack);
			int intvalue = variable_value_get_integer(value);
		}
		break;

		case PAUSE:
			return 0;
			break;

		case POP_LOCAL_VARIABLE:
		{
			VariableValue* value = variable_stack->pop_value(variable_stack);
			const char* varname = scn_fetch_string(code);
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

ScriptInterpreter* script_interpreter_create(
	VariableCollection* gobal_variables,
	FN_ROUTINE fn_routine)
{
	ScriptInterpreter* si = xmalloc(sizeof(*si));

	si->global_variables = gobal_variables;
	si->fn_routine = fn_routine;

	return si;
}

void script_interpreter_delete(ScriptInterpreter* si)
{
	free(si);
}