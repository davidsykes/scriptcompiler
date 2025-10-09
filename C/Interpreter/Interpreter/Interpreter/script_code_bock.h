#pragma once
#include "common_includes.h"


typedef struct ScriptCodeBlock ScriptCodeBlock;

typedef struct ScriptCodeBlockVTable {
	int (*fetch_int)(struct ScriptCodeBlock* self);
} ScriptCodeBlockVTable;


typedef struct ScriptCodeBlock {
	struct ScriptCodeBlockVTable* _vtable;
	const char* script_data;
	int script_pointer;
} ScriptCodeBlock;


void script_code_block_initialise();
ScriptCodeBlock* script_code_block_create(const char* scriptData);
void script_code_block_delete(ScriptCodeBlock*);