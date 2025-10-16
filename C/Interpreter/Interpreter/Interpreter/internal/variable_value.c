#include <string.h>
#include "../internal/xalloc.h"
#include "variable_value.h"

VariableValue* variable_value_create_integer(int integer)
{
	VariableValue* value = xmalloc(sizeof(*value));
	value->is_integer = 1;
	value->integer = integer;
	return value;
}

VariableValue* variable_value_create_string(const char* str)
{
	VariableValue* value = xmalloc(sizeof(*value));
	size_t len = strlen(str) + 1;
	value->string = xmalloc(len);
	value->is_integer = 0;
	memcpy(value->string, str, len);
	return value;
}

VariableValue* variable_value_create_copy(VariableValue* value)
{
	if (value->is_integer)
	{
		return variable_value_create_integer(value->integer);
	}
	else
	{
		return variable_value_create_string(value->string);
	}
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
