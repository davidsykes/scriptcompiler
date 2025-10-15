#include <stdlib.h>
#include <string.h>
#include "../internal/xalloc.h"
#include "variable_collection.h"
#include "variable_value.h"


typedef struct VariableItem {
	const char* key;
	VariableValue* variable;
} VariableItem;

typedef struct VariableCollection {
	VariableItem* variables;
	size_t count;
	size_t capacity;
} VariableCollection;


VariableCollection* variable_collection_create()
{
	VariableCollection* variable_collection = xmalloc(sizeof(*variable_collection));
	variable_collection->capacity = INITIAL_VARIABLE_COLLECTION_CAPACITY;
	variable_collection->count = 0;
	variable_collection->variables = xmalloc(variable_collection->capacity * sizeof(VariableItem));
	return variable_collection;
}

void variable_collection_delete(VariableCollection* collection)
{
	free(collection);
}

static void ensure_capacity(VariableCollection* collection)
{
	if (collection->count >= collection->capacity) {
		collection->capacity *= 2;
		collection->variables = xreallocarray(
			collection->variables,
			collection->capacity,
			sizeof(VariableItem));
	}
}

static char* create_string(const char* str)
{
	size_t len = strlen(str);
	char* new_str = xmalloc(len + 1);
	strcpy_s(new_str, len + 1, str);
	return new_str;
}

static VariableValue* create_variable(VariableCollection* collection, const char* name)
{
	ensure_capacity(collection);
	VariableValue* variable = variable_value_create(0);
	collection->variables[collection->count].key = create_string(name);
	collection->variables[collection->count].variable = variable;
	collection->count++;
	return variable;
}

static VariableValue* find_or_create_variable(
	VariableCollection* collection,
	const char* name)
{
	for (size_t i = 0; i < collection->count; i++) {
		if (strcmp(collection->variables[i].key, name) == 0) {
			return collection->variables[i].variable;
		}
	}
	return create_variable(collection, name);
}

void variable_collection_set_variable(
	VariableCollection* collection, const char* name, VariableValue* value)
{
	VariableValue* variable = find_or_create_variable(collection, name);
	variable_value_set_integer(variable, value->integer);
}

VariableValue* variable_collection_get_variable(
	VariableCollection* collection, const char* name)
{
	VariableValue* variable = find_or_create_variable(collection, name);
	return variable_value_create(variable->integer);
}