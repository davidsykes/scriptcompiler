using System;
using System.IO;

namespace Interpreter
{
    public class ScriptInterpreter : IScriptInterpreter
    {
        public ScriptInterpreter(BinaryReader script)
        {
            if (script == null) throw new ArgumentNullException();
        }

        public void Run()
        {
            
        }
    }
}
