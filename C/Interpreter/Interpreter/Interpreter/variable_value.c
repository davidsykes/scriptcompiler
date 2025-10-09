#include "variable_value.h"



VariableValue* variable_value_create(int _value)
{
	VariableValue* value = (VariableValue*)malloc(sizeof(VariableValue));
	if (value)
	{
		value->value = _value;
	}
	return value;
}

void variable_value_delete(VariableValue* value)
{
	free(value);
}


