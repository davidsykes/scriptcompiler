using Interpreter;

namespace ScriptRunner
{
    public class ScriptRunningInstance
    {
        public ScriptRunningInstance(SingleScript scriptToRun)
        {
            ProgramCounter = new ProgramCounter();
            VariablesManager = new VariablesManager();
            ProgramCounter.SetScript(scriptToRun);
        }

        public ProgramCounter ProgramCounter { get; }
        public VariablesManager VariablesManager { get; }
    }
}
