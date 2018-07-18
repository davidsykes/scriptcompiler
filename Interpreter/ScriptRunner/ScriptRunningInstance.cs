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
        public ScriptRunningInstance
        {
            var valueStack = new ValueStack();
            var programCounter = new ProgramCounter(scriptCollection[scriptToRun]);
            var localVariables = new VariablesManager();
        }

        public SetScriptToRun(string scriptName)
        {
            
        }
}
}
