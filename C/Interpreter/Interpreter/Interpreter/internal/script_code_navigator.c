#include <stdint.h>
#include <string.h>
#include "xalloc.h"
#include "script_code_navigator.h"

typedef struct ScriptCodeNavigator {
	const char* script_data;
	size_t script_pointer;
} ScriptCodeNavigator;


int scn_fetch_int(struct ScriptCodeNavigator* code)
{
	int v = *((int32_t*)(code->script_data + code->script_pointer));
	code->script_pointer += sizeof(int32_t);
	return v;
}

const char* scn_fetch_string(struct ScriptCodeNavigator* code)
{
	const char* s = code->script_data + code->script_pointer;
	code->script_pointer += strlen(s) + 1;
	return s;
}


void scn_jump(struct ScriptCodeNavigator* code, int distance)
{
	code->script_pointer += distance;
}

ScriptCodeNavigator* script_code_navigator_create(const char* scriptData)
{
	ScriptCodeNavigator* code = xmalloc(sizeof(*code));

	code->script_data = scriptData;
	code->script_pointer = 0;

	return code;
}

void script_code_navigator_delete(ScriptCodeNavigator* code)
{
	xfree(code);
}