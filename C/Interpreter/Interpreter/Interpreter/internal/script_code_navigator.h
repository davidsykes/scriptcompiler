#pragma once


typedef struct ScriptCodeNavigator ScriptCodeNavigator;


ScriptCodeNavigator* script_code_navigator_create(const char* scriptData);
void script_code_navigator_delete(ScriptCodeNavigator*);
int scn_fetch_int(struct ScriptCodeNavigator* code);
const char* scn_fetch_string(struct ScriptCodeNavigator* code);
void scn_jump(struct ScriptCodeNavigator* code, int distance);