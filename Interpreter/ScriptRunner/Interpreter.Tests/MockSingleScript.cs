namespace Interpreter.Tests
{
    class MockSingleScript : IProgramCounter
    {
        readonly List<object> _scriptCode = new List<object>();
        int _pc;

        public void SetScript(SingleScript script)
        {
            
        }

        public string GetScriptName()
        {
            return "Script Name";
        }

        public void AddCommand(ScriptToken command)
        {
            _scriptCode.Add((int)command);
        }

        public void AddIntValue(int value)
        {
            _scriptCode.Add(value);
        }

        public void AddString(string str)
        {
            _scriptCode.Add(str);
        }

        public int GetCommand()
        {
            return (int)GetNextToken();
        }

        public int GetInteger()
        {
            return GetCommand();
        }

        public string GetLengthPrefixedString()
        {
            return (string)GetNextToken();
        }

        public string GetNullTerminatedString()
        {
            return (string)GetNextToken();
        }

        object GetNextToken()
        {
            return _scriptCode[_pc++];
        }

        public int JumpDistance { get; private set; }

        public long PC => 0;

        public void MoveScriptPointer(int distance)
        {
            JumpDistance = distance;
        }

        public bool Eof => _pc >= _scriptCode.Count;
    }
}
