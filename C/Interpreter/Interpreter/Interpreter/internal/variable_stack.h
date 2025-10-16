#pragma once
#include "variable_value.h"


typedef struct VariableStack {
    void (*push_value)(struct VariableStack* stack, VariableValue* value);
	VariableValue*(*pop_value)(struct VariableStack* stack);
	VariableValue** values;
    int pointer;
} VariableStack;

VariableStack* variable_stack_create();
void variable_stack_delete(VariableStack* stack);
