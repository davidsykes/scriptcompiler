#pragma once


typedef struct ScriptCodeNavigator ScriptCodeNavigator;

typedef struct ScriptCodeNavigatorFnTable {
	int (*fetch_int)(struct ScriptCodeNavigator* self);
	const char* (*fetch_string)(struct ScriptCodeNavigator* self);
} ScriptCodeNavigatorFnTable;


typedef struct ScriptCodeNavigator {
	const ScriptCodeNavigatorFnTable* fn;
	const char* script_data;
	size_t script_pointer;
} ScriptCodeNavigator;

ScriptCodeNavigator* script_code_navigator_create(const char* scriptData);
void script_code_navigator_delete(ScriptCodeNavigator*);