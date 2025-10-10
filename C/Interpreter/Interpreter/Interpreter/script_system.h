

typedef struct ScriptSystem {
	int (*interpret)(struct ScriptSystem* script_system, const char* script);
} ScriptSystem;

