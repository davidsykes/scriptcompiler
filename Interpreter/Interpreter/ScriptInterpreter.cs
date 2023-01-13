using System;
using System.Collections.Generic;

namespace Interpreter
{
    public class ScriptInterpreter : IScriptInterpreter
    {
        readonly IFnRoutinesCaller _fnRoutinesCaller;
        readonly IValueStack _stack;
        readonly IVariableManager _variableManager;

        public ScriptInterpreter(
            IFnRoutinesCaller fnRoutinesCaller,
            IVariableManager variableManager,
            IValueStack stack
            )
        {
            if (fnRoutinesCaller == null) throw new ArgumentNullException();
            _fnRoutinesCaller = fnRoutinesCaller;
            if (stack == null) throw new ArgumentNullException();
            _stack = stack;
            if (variableManager == null) throw new ArgumentNullException();
            _variableManager = variableManager;
        }

        public bool Run(IProgramCounter programCounter, IVariableManager localVariables)
        {
            while (RunScriptCommand(programCounter, localVariables))
            {
            }
			return	programCounter.Eof;
        }

       	bool RunScriptCommand(IProgramCounter programCounter, IVariableManager localVariables)
        {
            if (programCounter.Eof)
                throw new Exception($"Unexpected end of script found in '{programCounter.GetScriptName()}'");

            var command = programCounter.GetCommand();

            switch ((ScriptToken) command)
            {
                case ScriptToken.PushIntValue:
                    _stack.PushValue(programCounter.GetInteger());
                    break;

                case ScriptToken.PushStringValue:
                    _stack.PushValue(programCounter.GetNullTerminatedString());
                    break;

                case ScriptToken.PushGlobalVariable: //  4
                    PushGlobalVariableOnToTheStack(programCounter);
                    break;

                case ScriptToken.PopGlobalVariable: //  5
                    SetGlobalVariableToBottomValueOfStack(programCounter);
                    break;

                case ScriptToken.Jfalse: //  6
                    MoveScriptPointerIfStackValueIsZero(programCounter);
                    break;

                case ScriptToken.Jtrue: //  7
                    MoveScriptPointerIfStackValueIsNotZero(programCounter);
                    break;

                case ScriptToken.Jall: //  8
                    MoveScriptPointerAlways(programCounter);
                    break;

                case ScriptToken.Add: //  9
                    _stack.Add();
                    break;

                case ScriptToken.Subtract: //  10
                    _stack.Subtract();
                    break;

                case ScriptToken.Multiply: //  11
                    _stack.Multiply();
                    break;

                case ScriptToken.Divide: //  12
                    _stack.Divide();
                    break;

                case ScriptToken.Negate: //  13
                    _stack.Negate();
                    break;

                case ScriptToken.LogicalNot: //  14
                    _stack.LogicalNot();
                    break;

                case ScriptToken.Lt: //  15
                    _stack.Lt();
                    break;

                case ScriptToken.Gt: //  16
                    _stack.Gt();
                    break;

                case ScriptToken.Lte: //  17
                    _stack.Lte();
                    break;

                case ScriptToken.Gte: //  18
                    _stack.Gte();
                    break;

                case ScriptToken.VariableEquals: //  19
                    _stack.VariableEquals();
                    break;

                case ScriptToken.LogicalAnd: //  20
                    _stack.LogicalAnd();
                    break;

                case ScriptToken.LogicalOr: //  21
                    _stack.LogicalOr();
                    break;

                case ScriptToken.CallFnRoutine: //  22
                    ProcessFnRoutine(programCounter, localVariables);
                    break;

                case ScriptToken.DropStackValue: //  23
                    return _stack.PopValue() == 0;

                case ScriptToken.EndScript: //  24
                    return false;

                case ScriptToken.DropSkipPauseNotZero: //  25
                    return ProcessDropSkipPauseNotZero(programCounter);

                case ScriptToken.PauseScript: // 26
                    return false;

                case ScriptToken.PushLocalVariable: //  27
                    PushLocalVariableOnToTheStack(programCounter, localVariables);
                    break;

                case ScriptToken.PopLocalVariable: //  28
                    SetLocalVariableToBottomValueOfStack(programCounter, localVariables);
                    break;

                default:
                    throw new InvalidOperationException($"Invalid Script Command {command}");
            }

            return true;
        }

        void PushGlobalVariableOnToTheStack(IProgramCounter programCounter)
        {
            var variableName = programCounter.GetNullTerminatedString();
            var value = _variableManager.GetVariable(variableName);
            _stack.PushValue(value);
        }

        void SetGlobalVariableToBottomValueOfStack(IProgramCounter programCounter)
        {
            var value = _stack.PopValue();
            var variableName = programCounter.GetNullTerminatedString();
            _variableManager.SetVariable(variableName, value);
        }

        void SetLocalVariableToBottomValueOfStack(IProgramCounter programCounter, IVariableManager localVariables)
        {
            var value = _stack.PopValue();
            var variableName = programCounter.GetNullTerminatedString();
            localVariables.SetVariable(variableName, value);
        }

        void PushLocalVariableOnToTheStack(IProgramCounter programCounter, IVariableManager localVariables)
        {
            var variableName = programCounter.GetNullTerminatedString();
            var value = localVariables.GetVariable(variableName);
            _stack.PushValue(value);
        }

        void ProcessFnRoutine(IProgramCounter programCounter, IVariableManager localVariables)
        {
            var parameterCount = programCounter.GetInteger();
            var fnRoutineName = programCounter.GetNullTerminatedString();

            var parameters = GetStackParametersIfRequired(parameterCount);

            var result = _fnRoutinesCaller.CallFnRoutine(localVariables, fnRoutineName, parameters);
            _stack.PushValue(result);
        }

        void MoveScriptPointerIfStackValueIsNotZero(IProgramCounter programCounter)
        {
            var distance = programCounter.GetInteger();
            if (_stack.PopValue() != 0)
                programCounter.MoveScriptPointer(distance - 4);
        }

        void MoveScriptPointerIfStackValueIsZero(IProgramCounter programCounter)
        {
            var distance = programCounter.GetInteger();
            if (_stack.PopValue() == 0)
                programCounter.MoveScriptPointer(distance);
        }

        void MoveScriptPointerAlways(IProgramCounter programCounter)
        {
            var distance = programCounter.GetInteger();
            programCounter.MoveScriptPointer(distance);
        }

        List<object> GetStackParametersIfRequired(int parameterCount)
        {
            return parameterCount > 0 ? _stack.PopValues(parameterCount) : new List<object>();
        }

        bool ProcessDropSkipPauseNotZero(IProgramCounter programCounter)
        {
            var distance = programCounter.GetInteger();
            var value = _stack.PopValue();

            switch (value)
            {
                case (int)ScriptReturn.Continue:
                    return true;

                case (int)ScriptReturn.PauseRepeat:
                    programCounter.MoveScriptPointer(distance - 4);
                    return false;

                case (int)ScriptReturn.Pause:
                    return false;
            }

            return true;
        }
    }
}