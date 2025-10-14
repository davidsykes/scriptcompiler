
#pragma once


typedef struct ScriptCode {
	const char* script;
} ScriptCode;

ScriptCode* script_code_create(const char* script);

