#pragma once
#include <stdlib.h>

typedef struct ScriptCodeBlock {
	const char* script_data;
	int script_pointer;
    int (*fetch_int)(struct ScriptCodeBlock* self);
} ScriptCodeBlock;


ScriptCodeBlock* script_code_block_create(const char* scriptData);
void script_code_block_delete(ScriptCodeBlock*);