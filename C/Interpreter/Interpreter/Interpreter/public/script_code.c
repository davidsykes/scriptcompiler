#include "../internal/xalloc.h"
#include "script_code.h"




ScriptCode* script_code_create(const char* script)
{
	ScriptCode* code = xmalloc(sizeof(*code));
	code->script = script;
	return code;
}