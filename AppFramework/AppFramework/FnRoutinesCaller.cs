using Interpreter;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AppFramework
{
    class FnRoutinesCaller : IFnRoutinesCaller
    {
        public int CallFnRoutine(IVariableManager localVariables, string fnRoutineName, List<object> parameters)
        {
            var paramlist = String.Join(",", parameters.Select(p => p.ToString()));

            Console.WriteLine($"fn routine {fnRoutineName} with ({paramlist})");

            return 0;
        }
    }
}
