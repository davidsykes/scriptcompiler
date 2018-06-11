using System;
using System.Collections.Generic;

namespace Interpreter
{
    public class FnRoutinesCaller : IFnRoutinesCaller
    {
        public int CallFnRoutine(string fnRoutineName, List<object> parameters)
        {
            Console.WriteLine($"fn routine {fnRoutineName} with {parameters.ToString()}");

            return 1;
        }
    }
}
