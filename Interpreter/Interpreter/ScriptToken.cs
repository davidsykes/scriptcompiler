namespace Interpreter
{
    public enum ScriptToken
    {
        PushIntValue = 1,
        PushStringValue = 3,
        PushGlobalVariable = 4,
        PopGlobalVariable = 5,
        Jfalse = 6,
        Jtrue = 7,
        Jall = 8,
        Add = 9,
        Subtract = 10,
        Multiply = 11,
        Divide = 12,
        Negate = 13,
        LogicalNot = 14,
        Lt = 15,
        Gt = 16,
        Lte = 17,
        Gte = 18,
        VariableEquals = 19,
        LogicalOr = 21,
        CallFnRoutine = 22,
        DropStackValue = 23,
        EndScript = 24,
        DropSkipPauseNotZero = 25,
        PauseScript = 26,
        PushLocalVariable = 27,
        PopLocalVariable = 28
    }
}
