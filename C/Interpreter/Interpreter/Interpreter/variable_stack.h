#pragma once
#include <stdlib.h>


typedef struct VariableStack {
    int (*push_value)(int value);
} VariableStack;

VariableStack* variable_stack_create();
void variable_stack_delete(VariableStack*);
