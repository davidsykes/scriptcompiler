#pragma once


//typedef struct VariableValueVTable {
//	void (*push_value)(struct VariableStack* stack, int value);
//} VariableValueVTable;
//

typedef struct VariableValue {
	//struct VariableValueVTable* _vtable;
	int value;
} VariableValue;


VariableValue* variable_value_create(int value);
void variable_value_delete(VariableValue*);