#pragma once


typedef struct VariableValue {
	int integer;
} VariableValue;


VariableValue* variable_value_create(int value);
void variable_value_delete(VariableValue*);

void variable_value_set_integer(VariableValue* value, int integer);
int variable_value_get_integer(VariableValue* value);