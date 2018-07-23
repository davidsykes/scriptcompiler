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
                var nameOfScriptToRun = args[1];

                CheckScriptPathIsValid(scriptPath);

                var scriptCollection = LoadScriptCollectionFromScriptFile(scriptPath);

                CheckNameOfScriptToRunIsValid(scriptCollection, nameOfScriptToRun);

                var scriptSystem = new ScriptSystem();

                var player1 = new ScriptRunningInstance(scriptCollection["Player1Script"]);
                while (!scriptSystem.Run(player1))
                {
                }

                var player2 = new ScriptRunningInstance(scriptCollection["Player2Script"]);
                while (!scriptSystem.Run(player2))
                {
                }

                player1 = new ScriptRunningInstance(scriptCollection[nameOfScriptToRun]);
                player2 = new ScriptRunningInstance(scriptCollection[nameOfScriptToRun]);
                scriptSystem.Run(player1);
                scriptSystem.Run(player2);
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
            }
            Console.WriteLine("Done");
        }

        static Dictionary<string, SingleScript> LoadScriptCollectionFromScriptFile(string scriptPath)
        {
            return ScriptLoader.LoadScripts(CreateBinaryReaderForScriptFile(scriptPath));
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

        static void CheckNameOfScriptToRunIsValid(Dictionary<string, SingleScript> scriptCollection, string scriptToRun)
        {
            if (scriptCollection == null) throw new ArgumentNullException(nameof(scriptCollection));
            if (!scriptCollection.ContainsKey(scriptToRun))
                throw new ArgumentException($"Script '{scriptToRun}' not found");
        }
    }
    
}


