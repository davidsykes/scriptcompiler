// (c) David Sykes 2013
// One more time, for the kids!

#include <stdint.h>
#include <stdlib.h> // Add this line to fix 'malloc' undefined error
#include "script_code_bock.h"
#include "variable_stack.h"

#define ERR_INVALID_OPCODE 1

#define pushintvalue 1
		/*
			pushparam = 2
	pushstring = 3
	pushvariable = 4
	popvariable = 5
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
	callfnroutine = 22
	dropstackvalue = 23
	endscript = 24
*/

typedef struct {
	ScriptCodeBlock* code_block;
	VariableStack* variable_stack;
} Arena;

static Arena* AllocateArena(const char* scriptData)
{
	Arena* arena = (Arena*)malloc(sizeof(Arena));
	if (!arena) return NULL;


	arena->code_block = script_code_block_create(scriptData);
	arena->variable_stack = variable_stack_create();

	return arena;
}

static void DeallocateArena(Arena* arena)
{
	script_code_block_delete(arena->code_block);
	variable_stack_delete(arena->variable_stack);

	free(arena);
}

int main_c(const char* scriptData)
{
	Arena* arena = AllocateArena(scriptData);
	ScriptCodeBlock* code = arena->code_block;
	VariableStack* variable_stack = arena->variable_stack;

	while (1)
	{
		int opcode = code->fetch_int(arena->code_block);

		switch (opcode)
		{
		case pushintvalue:
			variable_stack->push_value(code->fetch_int(arena->code_block));
			break;

		default:
			DeallocateArena(arena);
			return ERR_INVALID_OPCODE;
		}
	}
}
