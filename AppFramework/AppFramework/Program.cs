using System;
using System.Collections.Generic;
using System.IO;
using AppFramework.Logic;
using Interpreter;

namespace AppFramework
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                var scriptArguments = new ScriptArguments(args);
                var scriptCollection = ScriptLoader.LoadScripts(CreateBinaryReaderForScriptFile(scriptArguments.ScriptPath));
                CheckScriptNameIsValid(scriptCollection, scriptArguments.ScriptToRun);

                var fnRoutinesCaller = new FnRoutinesCaller();
                var globalVariablesManager = new VariablesManager();
                var localVariablesManager = new VariablesManager();
                var stack = new ValueStack();
                var scriptInterpreter = new ScriptInterpreter(fnRoutinesCaller, globalVariablesManager, stack);
                var programCounter = new ProgramCounter();
                programCounter.SetScript(scriptCollection[scriptArguments.ScriptToRun]);
                scriptInterpreter.Run(programCounter, localVariablesManager);
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
            Console.WriteLine("Done");
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
