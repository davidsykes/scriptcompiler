
namespace Interpreter
{
    public class SingleScript
    {
        byte[] _scriptData;

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
