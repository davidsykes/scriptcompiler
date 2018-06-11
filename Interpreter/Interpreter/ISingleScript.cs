
namespace Interpreter
{
    public interface ISingleScript
    {
        int GetCommand();
        int GetInteger();
        string GetLengthPrefixedString();
        string GetNullTerminatedString();
        bool Eof { get; }
        void MoveScriptPointer(int distance);
    }
}
