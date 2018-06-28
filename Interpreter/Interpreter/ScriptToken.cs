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
        DropSkipPauseNotZero
    }
}
