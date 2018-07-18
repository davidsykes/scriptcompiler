using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Interpreter;

namespace ScriptRunner
{
    class ScriptRunningInstance
    {
        ValueStack valueStack;
        ProgramCounter programCounter;
        VariablesManager localVariables;

        public ScriptRunningInstance()
        {
            var valueStack = new ValueStack();
            var programCounter = new ProgramCounter();
            var localVariables = new VariablesManager();
        }

        public void SetScriptToRun(SingleScript scriptToRun)
        {
            programCounter.SetScript(scriptToRun);
        }
}
}
