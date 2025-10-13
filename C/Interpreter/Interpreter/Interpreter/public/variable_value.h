#pragma once


typedef struct VariableValue {
	int value;
} VariableValue;


VariableValue* variable_value_create(int value);
void variable_value_delete(VariableValue*);