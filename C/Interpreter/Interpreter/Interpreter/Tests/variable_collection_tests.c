#include <assert.h>
#include <string.h>
#include "test_rig.h"
#include "../internal/variable_collection.h"
#include "../internal/xalloc.h"

typedef struct VariableCollectionTestsContext {
	VariableCollection* collection;
	VariableValue* var;
} VariableCollectionTestsContext;

static void a_new_global_variable_can_be_set_and_retrieved(VariableCollectionTestsContext* context)
{
	variable_collection_set_variable(
		context->collection,
		"Variable Name",
		context->var);

	VariableValue* var2 = variable_collection_get_variable(
		context->collection,
		"Variable Name");

	assert(var2->integer == 47);
}

static void an_existing_global_variable_can_be_set_and_retrieved(VariableCollectionTestsContext* context)
{
	variable_collection_set_variable(
		context->collection,
		"Variable Name",
		context->var);

	variable_value_set_integer(context->var, 55);

	variable_collection_set_variable(
		context->collection,
		"Variable Name",
		context->var);

	VariableValue* var2 = variable_collection_get_variable(
		context->collection,
		"Variable Name");

	assert(var2->integer == 55);
}

static void the_name_and_variable_pointer_are_mainained_internally(VariableCollectionTestsContext* context)
{
	const char* variable_name = "Variable Name";
	size_t name_len = strlen(variable_name)+1;
	char* name = xmalloc(MEM_TEST, name_len);
	strcpy_s(name, name_len, "Variable Name");
	VariableValue* var = variable_value_create_integer(470);

	variable_collection_set_variable(
		context->collection,
		name,
		var);

	strcpy_s(name, 12, "bla bla bla");
	var->integer = 99;

	VariableValue* var2 = variable_collection_get_variable(
		context->collection,
		"Variable Name");

	assert(var2->integer == 470);

	free(name);
}

static void* variable_collection_tests_set_up()
{
	VariableCollectionTestsContext* context = xmalloc(MEM_TEST, sizeof(*context));
	context->collection = variable_collection_create();
	context->var = variable_value_create_integer(47);
	return context;
}

static void variable_collection_tests_tear_down(void* _context)
{
	VariableCollectionTestsContext* context = _context;
	variable_value_delete(context->var);
	variable_collection_delete(context->collection);
	free(_context);
}

void run_variable_collection_tests()
{
	void (*tests[])(void* context) = {
	a_new_global_variable_can_be_set_and_retrieved,
	an_existing_global_variable_can_be_set_and_retrieved,
	the_name_and_variable_pointer_are_mainained_internally,
	0
	};

	run_test_rig(
		variable_collection_tests_set_up,
		variable_collection_tests_tear_down,
		tests
	);
}