
namespace Interpreter
{
    public interface IVariableManager
    {
        void SetVariable(string variableName, int value);
        int GetVariable(string variableName);
    }
}