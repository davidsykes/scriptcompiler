using System.Collections.Generic;

namespace Interpreter
{
    public class VariablesManager : IVariableManager
    {
        readonly Dictionary<string, int> _variables = new Dictionary<string, int>();

        // ---------------------------------------------------------------------
        public void SetVariable(string variableName, int value)
        {
            _variables[variableName] = value;
        }
        // ---------------------------------------------------------------------
        public int GetVariable(string variableName)
        {
            if (_variables.ContainsKey(variableName))
                return _variables[variableName];
            return 0;
        }
        // ---------------------------------------------------------------------
        public bool VariableExists(string variableName)//tonyAug21
        {
            return _variables.ContainsKey(variableName);
        }
        // ---------------------------------------------------------------------
        public int IncVariable(string variableName)//tony
        {
            //inc if exists
            if (_variables.ContainsKey(variableName))
                _variables[variableName]++;
            else
            {
                //first time
                _variables[variableName] = 1;
            }

            return _variables[variableName];
        }
        // ---------------------------------------------------------------------
        public int DecVariable(string variableName)//tonyOct21
        {
            //inc if exists
            if (_variables.ContainsKey(variableName))
                _variables[variableName]--;
            else
            {
                //first time - shaky ground
                _variables[variableName] = 0;
            }

            return _variables[variableName];
        }
        // ---------------------------------------------------------------------
#if UNITY_2021_1_OR_NEWER
        public void DebugDumpGlobals() //tonyDec20
        {
            Debug.Log("globals: " + _variables.Count);
            foreach (var gvar in _variables)
            {
                Debug.Log(gvar.Key+" = "+gvar.Value);
            }
        }
#endif
        // ---------------------------------------------------------------------
        public Dictionary<string, int> GiveVars()//tonyAug21
        {
            return _variables;
        }
        // ---------------------------------------------------------------------
        // ---------------------------------------------------------------------
    }

}
