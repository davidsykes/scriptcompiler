namespace Interpreter
{
    public enum ScriptToken
    {
        PushIntValue = 1,
        PushVariable = 4,
        PopVariable = 5,
        Add = 9,
        VariableEquals = 19,
        LogicalOr = 21,
        CallFnRoutine = 22,
        EndScript = 24
    }
}
