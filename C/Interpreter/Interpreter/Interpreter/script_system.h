typedef struct ScriptSystem {
	int (*interpret)(struct ScriptSystem* script_system, const char* script);
	void* system;
} ScriptSystem;



#ifdef __cplusplus
extern "C" {
#endif
	ScriptSystem* script_system_initialise();
#ifdef __cplusplus
}
#endif


