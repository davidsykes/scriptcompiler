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

        public void PushValue(string value)
        {
            _stack.Push(value);
        }

        public int PopValue()
        {
            if (_stack.Count <= 0) throw new StackOverflowException();

            return (int) _stack.Pop();
        }

        public bool IsEmpty => _stack.Count == 0;

        public List<object> PopValues(int parameterCount)
        {
            List<object> values = new List<object>();

            for (var pop = 1; pop <= parameterCount; pop += 1)
                values.Insert(0, _stack.Pop());

            return values;
        }

        public void Add()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            PushValue(PopValue() + PopValue());
        }

        public void Subtract()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            var value2 = PopValue();
            var value1 = PopValue();
            PushValue(value1 - value2);
        }

        public void Multiply()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            PushValue(PopValue() * PopValue());
        }

        public void Divide()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            var value2 = PopValue();
            var value1 = PopValue();

            PushValue(value1 / value2);
        }

        public void Negate()
        {
            if (_stack.Count < 1)
                throw new StackOverflowException("Stack Underflow");

            PushValue(-PopValue());
        }

        public void LogicalNot()
        {
            if (_stack.Count < 1)
                throw new StackOverflowException("Stack Underflow");

            PushValue(~PopValue());
        }

        public void VariableEquals()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            // ReSharper disable once EqualExpressionComparison
            PushValue(PopValue() == PopValue() ? 1 : 0);
        }

        public void LogicalOr()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            var a = PopValue() != 0;
            var b = PopValue() != 0;
            PushValue(a || b ? 1 : 0);
        }

        public void Lt()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            var value2 = PopValue();
            var value1 = PopValue();
            PushValue(value1 < value2 ? 1 : 0);
        }

        public void Lte()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            var value2 = PopValue();
            var value1 = PopValue();
            PushValue(value1 <= value2 ? 1 : 0);
        }

        public void Gt()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            var value2 = PopValue();
            var value1 = PopValue();
            PushValue(value1 > value2 ? 1 : 0);
        }

        public void Gte()
        {
            if (_stack.Count < 2)
                throw new StackOverflowException("Stack Underflow");

            var value2 = PopValue();
            var value1 = PopValue();
            PushValue(value1 >= value2 ? 1 : 0);
        }
    }
}