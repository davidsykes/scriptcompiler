
namespace Interpreter
{
    public interface IScriptInterpreter
    {
        bool Run(IProgramCounter programCounter, IVariableManager localVariables);
    }
}
