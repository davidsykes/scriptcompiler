
namespace Interpreter
{
    public interface IProgramCounter
    {
        void SetScript(SingleScript script);
        int GetCommand();
        int GetInteger();
        string GetLengthPrefixedString();
        string GetNullTerminatedString();
        bool Eof { get; }
        // ReSharper disable once InconsistentNaming
        long PC { get; }
        void MoveScriptPointer(int distance);
    }
}
