﻿using System;
using System.Collections.Generic;

namespace Interpreter
{
    public class ScriptInterpreter : IScriptInterpreter
    {
        readonly string _scriptName;
        readonly ISingleScript _scriptData;
        readonly IFnRoutinesCaller _fnRoutinesCaller;
        readonly IValueStack _stack;
        readonly IVariableManager _variableManager;

        public ScriptInterpreter(
            string scriptName,
            ISingleScript scriptData,
            IFnRoutinesCaller fnRoutinesCaller,
            IVariableManager variableManager,
            IValueStack stack)
        {
            _scriptName = scriptName;
            _scriptData = scriptData ?? throw new ArgumentNullException();
            _fnRoutinesCaller = fnRoutinesCaller ?? throw new ArgumentNullException();
            _stack = stack ?? throw new ArgumentNullException();
            _variableManager = variableManager ?? throw new ArgumentNullException();
        }

        public void Run()
        {
            while (RunScriptCommand())
            {
            }
        }

        bool RunScriptCommand()
        {
            if (_scriptData.Eof)
                throw new Exception($"Unexpected end of script found in '{_scriptName}'");

            var command = _scriptData.GetCommand();

            switch ((ScriptToken) command)
            {
                case ScriptToken.PushIntValue:
                    _stack.PushValue(_scriptData.GetInteger());
                    break;

                case ScriptToken.PushVariable:          //  4
                    PushVariableOnToTheStack();
                    break;

                case ScriptToken.PopVariable:           //  5
                    SetVariableToBottomValueOfStack();
                    break;

                case ScriptToken.Jfalse:                //  6
                    MoveScriptPointerIfStackValueIsZero();
                    break;

                case ScriptToken.Jtrue:                //  6
                    MoveScriptPointerIfStackValueIsNotZero();
                    break;

                case ScriptToken.Jall:                  //  8
                    MoveScriptPointerAlways();
                    break;

                case ScriptToken.Add:                   //  9
                    _stack.Add();
                    break;

                case ScriptToken.VariableEquals:        //  19
                    _stack.VariableEquals();
                    break;

                case ScriptToken.LogicalOr:             //  21
                    _stack.LogicalOr();
                    break;

                case ScriptToken.CallFnRoutine:         //  22
                    ProcessFnRoutine();
                    break;

                case ScriptToken.EndScript:
                    return false;

                default:
                    throw new InvalidOperationException($"Invalid Script Command {command}");
            }

            return true;
        }

        void PushVariableOnToTheStack()
        {
            var variableName = _scriptData.GetNullTerminatedString();
            var value = _variableManager.GetVariable(variableName);
            _stack.PushValue(value);
        }

        void SetVariableToBottomValueOfStack()
        {
            var value = _stack.PopValue();
            var variableName = _scriptData.GetNullTerminatedString();
            _variableManager.SetVariable(variableName, value);
        }

        void ProcessFnRoutine()
        {
            var parameterCount = _scriptData.GetInteger();
            var fnRoutineName = _scriptData.GetNullTerminatedString();

            var parameters = GetStackParametersIfRequired(parameterCount);

            var result = _fnRoutinesCaller.CallFnRoutine(fnRoutineName, parameters);
            _stack.PushValue(result);
        }

        void MoveScriptPointerIfStackValueIsNotZero()
        {
            var distance = _scriptData.GetInteger();
            if (_stack.PopValue() != 0)
                _scriptData.MoveScriptPointer(distance);
        }

        void MoveScriptPointerIfStackValueIsZero()
        {
            var distance = _scriptData.GetInteger();
            if (_stack.PopValue() == 0)
                _scriptData.MoveScriptPointer(distance);
        }

        void MoveScriptPointerAlways()
        {
            var distance = _scriptData.GetInteger();
            _scriptData.MoveScriptPointer(distance);
        }

        List<object> GetStackParametersIfRequired(int parameterCount)
        {
            return parameterCount > 0 ? _stack.PopValues(parameterCount) : new List<object>();
        }
    }
}