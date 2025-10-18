#pragma once
#include "script_instance.h"
#include "variable_collection.h"
#include "fn_routines.h"

typedef struct ScriptInterpreter ScriptInterpreter;


ScriptInterpreter* script_interpreter_create(
	VariableCollection* gobal_variables,
	FN_ROUTINE fn_routine);
void script_interpreter_delete(ScriptInterpreter*);

int script_interpreter_interpret(struct ScriptInterpreter* interpreter, ScriptInstance* script);

#define ERR_INVALID_OPCODE 2

#define PUSH_INT_VALUE 1
/*
	pushparam = 2
*/
#define PUSH_STRING_VALUE 3
/*
pushvariable = 4
*/
#define POP_VARIABLE 5
/*
jfalse = 6
jtrue = 7
jall = 8
add = 9
subtract = 10
multiply = 11
devide = 12
negate = 13
logicalnot = 14
lt = 15
gt = 16
lte = 17
gte = 18
equals = 19
logicaland = 20
logicalor = 21
*/
#define CALL_FN_ROUTINE		22
/*
dropstackvalue = 23
*/
#define ENDSCRIPT			24
#define DROPSKIPPAUSEREPEAT	25
#define PAUSE				26
#define POP_LOCAL_VARIABLE	28