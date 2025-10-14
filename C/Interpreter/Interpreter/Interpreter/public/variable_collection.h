#pragma once
#include "variable_value.h"


typedef struct VariableCollection VariableCollection;

VariableCollection* variable_collection_create();
void variable_collection_delete(VariableCollection* collection);

void variable_collection_set_variable(
	VariableCollection* collection, const char* name, VariableValue* value);
VariableValue* variable_collection_get_variable(
	VariableCollection* collection, const char* name);