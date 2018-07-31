using Interpreter;

namespace ScriptRunner
{
    class ScriptSystem
    {
        readonly ScriptInterpreter _interpreter;

        public ScriptSystem()
        {
            GlobalVariables = new VariablesManager();
            var fnRoutinesCaller = new FnRoutinesCaller(GlobalVariables);
            var valueStack = new ValueStack();
            _interpreter = new ScriptInterpreter(fnRoutinesCaller, GlobalVariables, valueStack);
        }

        public VariablesManager GlobalVariables { get; }

        public bool Run(ScriptRunningInstance player)
        {
            return _interpreter.Run(player.ProgramCounter, player.VariablesManager);
        }
    }
}
