#pragma once
#include "variable_value.h"


typedef struct VariableStack {
    void (*push_value)(struct VariableStack* stack, VariableValue* value);
	VariableValue*(*pop_value)(struct VariableStack* stack);
	VariableValue** values;
    int pointer;
	int stack_size;
} VariableStack;

void variable_stack_initialise();
VariableStack* variable_stack_create(int stack_size);
void variable_stack_delete(VariableStack* stack);
