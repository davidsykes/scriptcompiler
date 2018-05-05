using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ScriptRunner
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                CheckArgumentsHaveBeenSupplied();


                var scriptPath = args[0];
                CheckScriptPathIsValid(scriptPath);
                var scriptData = LoadScriptData(scriptPath);

                var scriptInterpreter = new ScriptInterpreter(scriptData);
                scriptInterpreter.Run();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
        }
    }
}


