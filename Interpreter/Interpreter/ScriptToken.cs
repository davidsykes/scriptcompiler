namespace Interpreter
{
    public enum ScriptToken
    {
        PushIntValue = 1,
        PushVariable = 4,
        PopVariable = 5,
        Jfalse = 6,
        Jtrue = 7,
        Jall = 8,
        Add = 9,
        Lt = 15,
        VariableEquals = 19,
        LogicalOr = 21,
        CallFnRoutine = 22,
        DropStackValue = 23,
        EndScript = 24
    }
}
