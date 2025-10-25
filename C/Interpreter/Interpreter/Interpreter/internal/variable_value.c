#include <string.h>
#include "../internal/xalloc.h"
#include "variable_value.h"


VariableValue* variable_value_create_integer(int integer)
{
	VariableValue* value = xmalloc(MEM_VARIABLE_VALUE, sizeof(*value));
	value->is_integer = 1;
	value->integer = integer;
	return value;
}

VariableValue* variable_value_create()
{
	VariableValue* value = xmalloc(MEM_VARIABLE_VALUE, sizeof(*value));
	value->is_integer = 1;
	value->integer = 0;
	return value;
}

VariableValue* variable_value_create_string(const char* str)
{
	VariableValue* value = xmalloc(MEM_VARIABLE_VALUE, sizeof(*value));
	size_t len = strlen(str) + 1;
	char *string = xmalloc(MEM_VARIABLE_VALUE, len);
	memcpy(string, str, len);
	value->string = string;
	value->is_integer = 0;
	return value;
}


void variable_value_copy(VariableValue* target, VariableValue* source)
{
	target->is_integer = source->is_integer;
	target->integer = source->integer;
	target->string = source->string;
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
	return value->integer;
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
