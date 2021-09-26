using System.Collections.Generic;

namespace Interpreter
{
    public interface IValueStack
    {
        void PushValue(int value);
        void PushValue(string value);
        int PopValue();
        bool IsEmpty { get; }
        List<object> PopValues(int parameterCount);
        void Add();
        void Subtract();
        void Multiply();
        void Divide();
        void Negate();
        void LogicalNot();
        void VariableEquals();
        void LogicalAnd();
        void LogicalOr();
        void Lt();
        void Lte();
        void Gt();
        void Gte();
    }
}
