
#pragma once


typedef struct ScriptCode {
	const char* script;
} ScriptCode;

ScriptCode* script_code_create(const char* script);
void script_code_delete(ScriptCode* script_code);
