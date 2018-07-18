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

        public int CallFnRoutine(string fnRoutineName, List<object> parameters)
        {
            if (_functions.ContainsKey(fnRoutineName))
            {
                return _functions[fnRoutineName](parameters);
            }

            var paramlist = String.Join(",", parameters.Select(p => p.ToString()));
            Console.WriteLine($"fn routine {fnRoutineName} with ({paramlist})");
            return 0;
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