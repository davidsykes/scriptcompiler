#pragma once


typedef struct VariableValue {
	int is_integer;
	int integer;
	char* string;
} VariableValue;


VariableValue* variable_value_create_integer(int value);
VariableValue* variable_value_create_string(const char* value);
VariableValue* variable_value_create_copy(VariableValue* value);
void variable_value_delete(VariableValue*);

void variable_value_set_integer(VariableValue* value, int integer);
int variable_value_get_integer(VariableValue* value);