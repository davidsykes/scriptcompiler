#include "../internal/xalloc.h"
#include "variable_value.h"

VariableValue* variable_value_create(int integer)
{
	VariableValue* value = xmalloc(sizeof(*value));
	value->integer = integer;
	return value;
}

void variable_value_delete(VariableValue* value)
{
	free(value);
}

void variable_value_set_integer(VariableValue* value, int integer)
{
	value->integer = integer;
}

int variable_value_get_integer(VariableValue* value)
{
	return value->integer;
}
