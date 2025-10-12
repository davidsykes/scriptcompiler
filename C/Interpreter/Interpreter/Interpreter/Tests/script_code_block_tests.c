#include "../internal\script_code_bock.h"
#include <string.h>
#include <assert.h>

static void a_code_block_can_be_created_and_destroyed()
{
	const char* test_code = "test";

	ScriptCodeBlock* code = script_code_block_create(test_code);

	script_code_block_delete(code);
}

static void an_integer_can_be_fetched()
{
	const char* test_code = "\x01\x02\x03\x04\x05\x06\x07\x08";

	ScriptCodeBlock* code = script_code_block_create(test_code);

	int v = code->_vtable->fetch_int(code);

	assert(v == 67305985);

	script_code_block_delete(code);
}

static void multiple_integers_can_be_fetched()
{
	int data[3] = { 42, 1234, 999 };

	ScriptCodeBlock* code = script_code_block_create((char*)&data);

	assert(code->_vtable->fetch_int(code) == 42);
	assert(code->_vtable->fetch_int(code) == 1234);
	assert(code->_vtable->fetch_int(code) == 999);

	script_code_block_delete(code);
}

static void multiple_strings_can_be_fetched()
{
	const char* test_code = "string1\x00str2\x00s3\x00";

	ScriptCodeBlock* code = script_code_block_create(test_code);

	assert(strcmp(code->_vtable->fetch_string(code), "string1") == 0);
	assert(strcmp(code->_vtable->fetch_string(code), "str2") == 0);
	assert(strcmp(code->_vtable->fetch_string(code), "s3") == 0);

	script_code_block_delete(code);
}

void run_script_code_block_tests()
{
	a_code_block_can_be_created_and_destroyed();
	an_integer_can_be_fetched();
	multiple_integers_can_be_fetched();
	multiple_strings_can_be_fetched();
}