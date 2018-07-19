using Interpreter;

namespace ScriptRunner
{
    class ScriptRunningInstance
    {
        
        public ScriptRunningInstance()
        {
            ProgramCounter = new ProgramCounter();
            VariablesManager = new VariablesManager();
        }

        public void SetScriptToRun(SingleScript scriptToRun)
        {
            ProgramCounter.SetScript(scriptToRun);
        }

        public ProgramCounter ProgramCounter { get; }
        public VariablesManager VariablesManager { get; }
    }
}
