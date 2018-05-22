using System;
using System.IO;
using Interpreter;

namespace ScriptRunner
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                CheckArgumentsHaveBeenSupplied(args);


                var scriptPath = args[0];
                CheckScriptPathIsValid(scriptPath);
                var scriptData = LoadScriptData(scriptPath);

                var scriptInterpreter = new ScriptInterpreter(scriptData);
                scriptInterpreter.Run();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }

        static void CheckArgumentsHaveBeenSupplied(string[] args)
        {
            if (args == null) throw new ArgumentNullException(nameof(args));
            if (args.Length != 2)
                throw new ArgumentException("Script path not supplied");
        }

        static void CheckScriptPathIsValid(string scriptPath)
        {
            if (!File.Exists(scriptPath))
                throw new ArgumentException($"Script file {scriptPath} not found");
        }

        static BinaryReader LoadScriptData(string scriptPath)
        {
            return new BinaryReader(File.Open(scriptPath, FileMode.Open));
        }

    }
}


