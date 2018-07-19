using Interpreter;

namespace ScriptRunner
{
    class ScriptSystem
    {
        ScriptInterpreter _interpreter;

        public ScriptSystem()
        {
            var variablesManager = new VariablesManager();
            var fnRoutinesCaller = new FnRoutinesCaller(variablesManager);
            var valueStack = new ValueStack();
            _interpreter = new ScriptInterpreter(fnRoutinesCaller, variablesManager, valueStack);
        }

        public bool Run(ScriptRunningInstance player)
        {
            return _interpreter.Run(player.ProgramCounter, player.VariablesManager);
        }
    }
}
