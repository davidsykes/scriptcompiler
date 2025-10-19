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

VariableValue* variable_value_create()
{
	VariableValue* value = xmalloc(sizeof(*value));
	value->is_integer = 1;
	value->integer = 0;
	return value;
}

VariableValue* variable_value_create_string(const char* str)
{
	VariableValue* value = xmalloc(sizeof(*value));
	size_t len = strlen(str) + 1;
	char *string = xmalloc(len);
	memcpy(string, str, len);
	value->string = string;
	value->is_integer = 0;
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
	value->is_integer = 1;
}

int variable_value_get_integer(VariableValue* value)
{
	//if (value->is_integer)
		return value->integer;
	//return 0;
}

void variable_value_set_string(VariableValue* value, const char* string)
{
	value->string = string;
	value->is_integer = 0;
}

const char* variable_value_get_string(VariableValue* value)
{
	if (value->is_integer)
		return 0;
	return value->string;
}
