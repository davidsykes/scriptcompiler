using System;
using System.Collections.Generic;
using System.Linq;
using Interpreter;

namespace ScriptRunner
{
    public class FnRoutinesCaller : IFnRoutinesCaller
    {
        public int CallFnRoutine(string fnRoutineName, List<object> parameters)
        {
            var paramlist = String.Join(",", parameters.Select(p => p.ToString()));

            Console.WriteLine($"fn routine {fnRoutineName} with ({paramlist})");

            return 1;
        }
    }
}
