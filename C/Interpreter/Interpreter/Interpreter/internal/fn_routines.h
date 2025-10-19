#pragma once

#include "variable_value.h"

typedef void (*FN_ROUTINE)(const char* name, VariableValue** parameters, int parameter_count, VariableValue* fn_return_value);