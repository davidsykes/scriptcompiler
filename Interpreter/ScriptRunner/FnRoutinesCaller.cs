using System;
using System.Collections.Generic;
using System.Linq;
using Interpreter;

namespace ScriptRunner
{
    public class FnRoutinesCaller : IFnRoutinesCaller
    {
        Dictionary<string, Func<List<object>, int>> _functions;
        readonly VariablesManager _variablesManager;

        public FnRoutinesCaller(VariablesManager variablesManager)
        {
            _variablesManager = variablesManager;
            AddFunction("DropSkipJump", DropSkipJumpNotZero);
        }

        void AddFunction(string name, Func<List<object>, int> fn)
        {
            _functions = new Dictionary<string, Func<List<object>, int>>();
            _functions.Add(name, fn);
        }

        public int CallFnRoutine(IVariableManager localVariables, string fnRoutineName, List<object> parameters)
        {
            if (FunctionListContainsFunctionToCall(fnRoutineName))
            {
                return CallFunctionWithParameters(fnRoutineName, parameters);
            }

            var paramlist = string.Join(",", parameters.Select(p => p.ToString()));
            Console.WriteLine($"fn routine {fnRoutineName} with ({paramlist})");
            return 0;
        }

        bool FunctionListContainsFunctionToCall(string fnRoutineName)
        {
            return _functions.ContainsKey(fnRoutineName);
        }

        int CallFunctionWithParameters(string fnRoutineName, List<object> parameters)
        {
            return _functions[fnRoutineName](parameters);
        }

        int DropSkipJumpNotZero(List<object> parameters)
        {
            var repeatValue = _variablesManager.GetVariable("repeat");
            _variablesManager.SetVariable("repeat", repeatValue - 1);
            Console.WriteLine($"Repeat count = {repeatValue}");
            return repeatValue > 0 ? 1 : 0;
        }
    }
}