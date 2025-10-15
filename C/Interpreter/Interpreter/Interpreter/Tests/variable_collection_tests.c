#include <assert.h>
#include "test_rig.h"
#include "../public/variable_collection.h"
#include "../internal/xalloc.h"

typedef struct VariableCollectionTestsContext {
	VariableCollection* collection;
	VariableValue* var;
} VariableCollectionTestsContext;

static void a_new_global_variable_can_be_set_and_retrieved(void* _context)
{
	VariableCollectionTestsContext* context = _context;

	variable_collection_set_variable(
		context->collection,
		"Variable Name",
		context->var);

	VariableValue* var2 = variable_collection_get_variable(
		context->collection,
		"Variable Name");

	assert(var2->integer == 47);
}

static void an_existing_global_variable_can_be_set_and_retrieved(void* _context)
{
	VariableCollectionTestsContext* context = _context;

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

static void the_name_and_variable_pointer_are_mainained_internally(void* _context)
{
	VariableCollectionTestsContext* context = _context;
	char* name = xmalloc(20);
	strcpy(name, "Variable Name");
	VariableValue* var = variable_value_create(470);

	variable_collection_set_variable(
		context->collection,
		name,
		var);

	strcpy(name, "bla bla bla");
	var->integer = 99;

	VariableValue* var2 = variable_collection_get_variable(
		context->collection,
		"Variable Name");

	assert(var2->integer == 470);

	free(name);
}

static void* variable_collection_tests_set_up()
{
	VariableCollectionTestsContext* context = xmalloc(sizeof(*context));
	context->collection = variable_collection_create(4);
	context->var = variable_value_create(47);
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