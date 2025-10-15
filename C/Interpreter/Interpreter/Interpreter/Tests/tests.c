
void run_script_code_block_tests();
void run_variable_stack_tests();
void run_script_interpreter_tests();
void run_variable_collection_tests();

void run_all_tests()
{
	run_script_code_block_tests();
	run_variable_stack_tests();
	run_variable_collection_tests();
	run_script_interpreter_tests();
}