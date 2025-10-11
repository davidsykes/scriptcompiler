#pragma once


typedef struct ScriptCodeBlock ScriptCodeBlock;

typedef struct ScriptCodeBlockVTable {
	int (*fetch_int)(struct ScriptCodeBlock* self);
	const char* (*fetch_string)(struct ScriptCodeBlock* self);
} ScriptCodeBlockVTable;


typedef struct ScriptCodeBlock {
	const ScriptCodeBlockVTable* _vtable;
	const char* script_data;
	int script_pointer;
} ScriptCodeBlock;

ScriptCodeBlock* script_code_block_create(const char* scriptData);
void script_code_block_delete(ScriptCodeBlock*);