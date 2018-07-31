using System.Collections.Generic;

namespace Interpreter
{
    public interface IFnRoutinesCaller
    {
        int CallFnRoutine(IVariableManager localVariables, string fnRoutineName, List<object> parameters);
    }
}