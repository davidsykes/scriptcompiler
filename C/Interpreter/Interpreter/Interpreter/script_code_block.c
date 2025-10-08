#include "script_code_bock.h"
#include <stdint.h> // Add this line to define int32_t


int fetch_int(struct ScriptCodeBlock* self);

ScriptCodeBlock* script_code_block_create(const char* scriptData)
{
	ScriptCodeBlock* code = (ScriptCodeBlock*)malloc(sizeof(ScriptCodeBlock));
	if (code == NULL) {
		return NULL;
	}

	code->script_data = scriptData;
	code->script_pointer = 0;
	code->fetch_int = fetch_int;

	return code;
}

void script_code_block_delete(ScriptCodeBlock* code)
{
	free(code);
}

int fetch_int(struct ScriptCodeBlock* code)
{
	int v = *((int32_t*)(code->script_data + code->script_pointer));
	code->script_pointer += sizeof(int32_t);
	return v;
}