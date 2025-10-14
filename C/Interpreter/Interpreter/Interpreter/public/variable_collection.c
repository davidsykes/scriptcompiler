#include "../internal/xalloc.h"
#include "variable_collection.h"
#include "variable_value.h"


typedef struct VariableCollection {
	const char* script_data;
	size_t script_pointer;
} VariableCollection;


VariableCollection* variable_collection_create(void)
{
	VariableCollection* variable_collection = xmalloc(sizeof(*variable_collection));
	return variable_collection;
}

void variable_collection_delete(VariableCollection* collection)
{
	free(collection);
}


void variable_collection_set_variable(
	VariableCollection* collection, const char* name, VariableValue* value)
{
	// Do nothing for now.
	(void)collection;
	(void)name;
	(void)value;
}

VariableValue* variable_collection_get_variable(
	VariableCollection* collection, const char* name)
{
	return variable_value_create(2);
}