#include <stdint.h>
#include <string.h>
#include "xalloc.h"
#include "script_code_navigator.h"

static int fetch_int(struct ScriptCodeNavigator* code)
{
	int v = *((int32_t*)(code->script_data + code->script_pointer));
	code->script_pointer += sizeof(int32_t);
	return v;
}

static const char* fetch_string(struct ScriptCodeNavigator* code)
{
	const char* s = code->script_data + code->script_pointer;
	code->script_pointer += strlen(s) + 1;
	return s;
}

static const ScriptCodeNavigatorFnTable _scriptCodeBlockFnTable = {
	.fetch_int = fetch_int,
	.fetch_string = fetch_string
};

ScriptCodeNavigator* script_code_navigator_create(const char* scriptData)
{
	ScriptCodeNavigator* code = xmalloc(sizeof(*code));

	code->fn = &_scriptCodeBlockFnTable;
	code->script_data = scriptData;
	code->script_pointer = 0;

	return code;
}

void script_code_navigator_delete(ScriptCodeNavigator* code)
{
	free(code);
}