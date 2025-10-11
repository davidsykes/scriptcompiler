#include "xalloc.h"
#include "script_code_bock.h"
#include <stdint.h>

static int fetch_int(struct ScriptCodeBlock* code)
{
	int v = *((int32_t*)(code->script_data + code->script_pointer));
	code->script_pointer += sizeof(int32_t);
	return v;
}

static const char* fetch_string(struct ScriptCodeBlock* code)
{
	int v = *((int32_t*)(code->script_data + code->script_pointer));
	code->script_pointer += sizeof(int32_t);
	return "v";
}

static const ScriptCodeBlockVTable _scriptCodeBlockVTable = {
	.fetch_int = fetch_int,
	.fetch_string = fetch_string
};

ScriptCodeBlock* script_code_block_create(const char* scriptData)
{
	ScriptCodeBlock* code = xmalloc(sizeof(*code));

	code->_vtable = &_scriptCodeBlockVTable;
	code->script_data = scriptData;
	code->script_pointer = 0;

	return code;
}

void script_code_block_delete(ScriptCodeBlock* code)
{
	free(code);
}