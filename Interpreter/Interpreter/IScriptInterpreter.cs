
namespace Interpreter
{
    public interface IScriptInterpreter
    {
        bool Run(IVariableManager localVariables);
    }
}
