namespace Interpreter
{
    public class SingleScript
    {
        string _name;
        readonly byte[] _scriptData;

        public SingleScript(string scriptName, byte[] scriptData)
        {
            _name = scriptName;
            _scriptData = scriptData;
        }

        public string Name => _name;

        public byte[] GetScriptBinary()
        {
            return _scriptData;
        }
    }
}
