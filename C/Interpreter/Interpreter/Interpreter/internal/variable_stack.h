#pragma once
#include "variable_value.h"

typedef struct VariableStack VariableStack;

VariableStack* variable_stack_create(void);
void variable_stack_delete(VariableStack* stack);

void vs_push_value(VariableStack* stack, VariableValue* value);
VariableValue* vs_pop_value(VariableStack* stack);
VariableValue** vs_get_parameter_pointer(VariableStack* stack, int parameter_count);