using System;
using System.Collections.Generic;

namespace Interpreter
{
    public class VariablesManager : IVariableManager
    {
        Dictionary<string, int> _variables = new Dictionary<string, int>();

        public void SetVariable(string variableName, int value)
        {
            Console.WriteLine($"Set variable '{variableName}' to {value}");
            _variables[variableName] = value;
        }

        public int GetVariable(string variableName)
        {
            if (_variables.ContainsKey(variableName))
                return _variables[variableName];
            return 0;
        }
    }
}
