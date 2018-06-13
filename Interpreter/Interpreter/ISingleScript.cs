
namespace Interpreter
{
    public interface ISingleScript
    {
        int GetCommand();
        int GetInteger();
        string GetLengthPrefixedString();
        string GetNullTerminatedString();
        bool Eof { get; }
        long PC { get; }
        void MoveScriptPointer(int distance);
    }
}
