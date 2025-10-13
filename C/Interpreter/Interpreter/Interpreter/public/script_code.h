#pragma once

typedef struct ScriptCode {
	const char* script;
} ScriptCode;

#ifdef __cplusplus
extern "C" {
#endif
	ScriptCode* script_code_create(const char* script);
#ifdef __cplusplus
}
#endif
