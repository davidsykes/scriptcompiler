using Interpreter;
using System;
using System.Collections.Generic;
using System.IO;

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
                var scriptToRun = args[1];

                CheckScriptPathIsValid(scriptPath);

                var scriptCollection = ScriptLoader.LoadScripts(CreateBinaryReaderForScriptFile(scriptPath));

                CheckScriptNameIsValid(scriptCollection, scriptToRun);

                var fnRoutinesCaller = new FnRoutinesCaller();
                var variablesManager = new VariablesManager();
                var stack = new ValueStack();
                var scriptInterpreter = new ScriptInterpreter(scriptToRun, scriptCollection[scriptToRun], fnRoutinesCaller, variablesManager, stack);
                scriptInterpreter.Run();
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
            Console.WriteLine("Done");
        }

        static void CheckArgumentsHaveBeenSupplied(string[] args)
        {
            if (args == null) throw new ArgumentNullException(nameof(args));
            if (args.Length != 2)
                throw new ArgumentException("Useage: {Script Path} {Script To Run}");
        }

        static void CheckScriptPathIsValid(string scriptPath)
        {
            if (!File.Exists(scriptPath))
                throw new ArgumentException($"Script file {scriptPath} not found");
        }

        static BinaryReader CreateBinaryReaderForScriptFile(string scriptPath)
        {
            return new BinaryReader(File.Open(scriptPath, FileMode.Open));
        }

        static void CheckScriptNameIsValid(Dictionary<string, SingleScript> scriptCollection, string scriptToRun)
        {
            if (scriptCollection == null) throw new ArgumentNullException(nameof(scriptCollection));
            if (!scriptCollection.ContainsKey(scriptToRun))
                throw new ArgumentException($"Script '{scriptToRun}' not found");
        }
    }
}


