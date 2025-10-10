#include "xalloc.h"
#include "variable_value.h"



VariableValue* variable_value_create(int _value)
{
	VariableValue* value = xmalloc(sizeof(*value));
	value->value = _value;
	return value;
}

void variable_value_delete(VariableValue* value)
{
	free(value);
}


