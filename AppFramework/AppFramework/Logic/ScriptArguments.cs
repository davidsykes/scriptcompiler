using System;
using System.IO;

namespace AppFramework.Logic
{
    internal class ScriptArguments
    {
        public string ScriptPath { get; private set; }
        public string ScriptToRun { get; private set; }

        public ScriptArguments(string[] args)
        {
            CheckArgumentsHaveBeenSupplied(args);
            ScriptPath = args[0];
            ScriptToRun = args[1];

            CheckScriptPathIsValid(ScriptPath);
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
    }
}
