using System.Collections.Generic;

namespace Interpreter
{
    public interface IFnRoutinesCaller
    {
        int CallFnRoutine(string fnRoutineName, List<object> parameters);
    }
}