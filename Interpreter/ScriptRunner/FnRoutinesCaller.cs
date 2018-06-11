using System;
using System.Collections.Generic;
using Interpreter;

namespace ScriptRunner
{
    public class FnRoutinesCaller : IFnRoutinesCaller
    {
        public int CallFnRoutine(string fnRoutineName, List<object> parameters)
        {
            Console.WriteLine($"fn routine {fnRoutineName} with {parameters}");

            return 1;
        }
    }
}
