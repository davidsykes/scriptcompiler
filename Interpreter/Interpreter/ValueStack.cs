using System;
using System.Collections;
using System.Collections.Generic;

namespace Interpreter
{
    public class ValueStack : IValueStack
    {
        readonly Stack _stack;

        public ValueStack()
        {
            _stack = new Stack();
        }

        public void PushValue(int value)
        {
            _stack.Push(value);
        }

        public int PopValue()
        {
            if (_stack.Count <= 0) throw new StackOverflowException();

            return (int)_stack.Pop();
        }

        public bool IsEmpty => _stack.Count == 0;

        public List<object> PopValues(int parameterCount)
        {
            throw new NotImplementedException();
        }

        public void Add()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            PushValue(PopValue() + PopValue());
        }

        public void LogicalOr()
        {
            
        }
    }
}
