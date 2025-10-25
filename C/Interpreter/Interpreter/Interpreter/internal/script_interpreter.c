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
			vs_push_value(variable_stack, value);
		}
		break;

		case PUSH_STRING_VALUE:
		{
			const char* string_value = scn_fetch_string(code);
			VariableValue* value = variable_value_create_string(string_value);
			vs_push_value(variable_stack, value);
		}
		break;

		case POP_VARIABLE:
		{
			const char* varname = scn_fetch_string(code);
			VariableValue* value = vs_pop_value(variable_stack);
			variable_collection_set_variable(
				interpreter->global_variables, varname, value);
		}
		break;

		case CALL_FN_ROUTINE:
		{
			int parameter_count = scn_fetch_int(code);
			const char* fnname = scn_fetch_string(code);
			VariableValue** parameters = vs_get_parameter_pointer(variable_stack, parameter_count);
			interpreter->fn_routine(fnname, parameters, parameter_count, script->fn_return_value);
			VariableValue* value_copy = variable_value_create_copy(script->fn_return_value);
			vs_push_value(variable_stack, value_copy);
		}
		break;

		case ENDSCRIPT:
			return SCRIPT_COMPLETED;

		case DROPSKIPPAUSEREPEAT:
		{
			int jump = scn_fetch_int(code);
			VariableValue* value = vs_pop_value(variable_stack);
			int intvalue = variable_value_get_integer(value);
			free(value);
			if (intvalue == DROPSKIPPAUSEREPEAT_PAUSE)
				return SCRIPT_PAUSED;
			if (intvalue == DROPSKIPPAUSEREPEAT_REPEAT)
			{
				scn_jump(code, jump - sizeof(int32_t));
				return SCRIPT_PAUSED;
			}
		}
		break;

		case PAUSE:
			return SCRIPT_PAUSED;
			break;

		case POP_LOCAL_VARIABLE:
		{
			VariableValue* value = vs_pop_value(variable_stack);
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
	ScriptInterpreter* si = xmalloc(MEM_SCRIPT_INTERPRETER, sizeof(*si));

	si->global_variables = gobal_variables;
	si->fn_routine = fn_routine;

	return si;
}

void script_interpreter_delete(ScriptInterpreter* si)
{
	xfree(si);
}