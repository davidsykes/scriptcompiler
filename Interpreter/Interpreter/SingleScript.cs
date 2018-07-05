namespace Interpreter
{
    public class SingleScript
    {
        readonly byte[] _scriptData;

        public SingleScript(byte[] scriptData)
        {
            _scriptData = scriptData;
        }

        public byte[] GetScriptBinary()
        {
            return _scriptData;
        }
    }
}
