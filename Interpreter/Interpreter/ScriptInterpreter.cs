using System;

namespace Interpreter
{
    public class ScriptInterpreter : IScriptInterpreter
    {
        public ScriptInterpreter(SingleScript scriptData)
        {
            if (scriptData == null) throw new ArgumentNullException();
        }

        public void Run()
        {
            
        }
    }
}
