#include "../internal\script_code_navigator.h"
#include <string.h>
#include <assert.h>
#include "test_rig.h"

static void a_code_block_can_be_created_and_destroyed(void* context)
{
	const char* test_code = "test";

	ScriptCodeNavigator* code = script_code_navigator_create(test_code);

	script_code_navigator_delete(code);
}

static void an_integer_can_be_fetched(void* context)
{
	const char* test_code = "\x01\x02\x03\x04\x05\x06\x07\x08";

	ScriptCodeNavigator* code = script_code_navigator_create(test_code);

	int v = scn_fetch_int(code);

	assert(v == 67305985);

	script_code_navigator_delete(code);
}

static void multiple_integers_can_be_fetched(void* context)
{
	int data[3] = { 42, 1234, 999 };

	ScriptCodeNavigator* code = script_code_navigator_create((char*)&data);

	assert(scn_fetch_int(code) == 42);
	assert(scn_fetch_int(code) == 1234);
	assert(scn_fetch_int(code) == 999);

	script_code_navigator_delete(code);
}

static void multiple_strings_can_be_fetched(void* context)
{
	const char* test_code = "string1\x00str2\x00s3\x00";

	ScriptCodeNavigator* code = script_code_navigator_create(test_code);

	assert(strcmp(scn_fetch_string(code), "string1") == 0);
	assert(strcmp(scn_fetch_string(code), "str2") == 0);
	assert(strcmp(scn_fetch_string(code), "s3") == 0);

	script_code_navigator_delete(code);
}

static void* script_code_navigator_tests_set_up()
{
	return 0;
}

static void script_code_navigator_tests_tear_down(void* _context)
{
}

void run_script_code_block_tests()
{
	void (*tests[])(void* context) = {
	a_code_block_can_be_created_and_destroyed,
	an_integer_can_be_fetched,
	multiple_integers_can_be_fetched,
	multiple_strings_can_be_fetched,
		0
	};

	run_test_rig(
		script_code_navigator_tests_set_up,
		script_code_navigator_tests_tear_down,
		tests
	);
}