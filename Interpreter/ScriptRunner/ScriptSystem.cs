using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Interpreter;

namespace ScriptRunner
{
    class ScriptSystem
    {
        public ScriptSystem()
        {
            var variablesManager = new VariablesManager();
            var fnRoutinesCaller = new FnRoutinesCaller(variablesManager);
            var scriptInterpreter = new ScriptInterpreter(scriptToRun, programCounter, fnRoutinesCaller, variablesManager, valueStack);
        }
    }
}
