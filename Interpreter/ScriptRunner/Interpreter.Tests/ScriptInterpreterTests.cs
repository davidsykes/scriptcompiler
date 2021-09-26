using FluentAssertions;
using Moq;
using NUnit.Framework;
using System;
using System.Collections.Generic;

namespace Interpreter.Tests
{

    [TestFixture]
    public class ScriptInterpreterTests
    {
        #region Fields

        Mock<IValueStack> _mockValueStack;
        Mock<IFnRoutinesCaller> _mockFnRoutinesCaller;
        MockSingleScript _script;
        Mock<IVariableManager> _mockGlobalVariableManager;
        Mock<IVariableManager> _mockLocalVariableManager;
        IScriptInterpreter _interpreter;
        List<object> _fnParamaters;

        #endregion

        #region Initialisation

        [Test]
        public void CreatingAScriptInterpreterWithNullFnRoutineCallerThrowsArgumentNullExceptionException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter(
                null, _mockGlobalVariableManager.Object, _mockValueStack.Object);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void CreatingAScriptInterpreterWithNullVariableManagerThrowsArgumentNullExceptionException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter(_mockFnRoutinesCaller.Object, null, _mockValueStack.Object);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void CreatingAScriptInterpreterWithNullValueStackThrowsArgumentNullExceptionException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter(
                _mockFnRoutinesCaller.Object, _mockGlobalVariableManager.Object, null);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void RunningAScriptWithAnInvalidInstructionThrowsAnException()
        {
            _script.AddIntValue(int.MaxValue);

            Action action = () => RunScriptInterpreter();

            action.Should().Throw<InvalidOperationException>().WithMessage("Invalid Script Command 2147483647");
        }

        #endregion

        #region 1 Push Int Value

        [Test]
        public void ThePushIntValueCommandPushesTheValueOnToTheStack()
        {
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 3 Push String Value

        [Test]
        public void ThePushStringValueCommandPushesTheValueOnToTheStack()
        {
            _script.AddCommand(ScriptToken.PushStringValue);
            _script.AddString("gimmer");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue("gimmer"));
        }

        #endregion

        #region 4 Push Global Variable

        [Test]
        public void ThePushGlobalVariableFetchesTheVariableValueFromTheGlobalVariableManager()
        {
            _script.AddCommand(ScriptToken.PushGlobalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockGlobalVariableManager.Verify(m => m.GetVariable("variable"));
        }

        [Test]
        public void ThePushlobalVariablePushesTheGlobalVariableValueOnToTheStack()
        {
            _mockGlobalVariableManager.Setup(m => m.GetVariable("variable")).Returns(42);

            _script.AddCommand(ScriptToken.PushGlobalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 5 Pop Global Variable

        [Test]
        public void ThePopGlobalVariableCommandPopsTheBottomValueOfTheStack()
        {
            _script.AddCommand(ScriptToken.PopGlobalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PopValue());
        }

        [Test]
        public void ThePopGlobalVariableCommandSetsAGlobalVariableWithTheBottomValueOfTheStack()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(42);

            _script.AddCommand(ScriptToken.PopGlobalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockGlobalVariableManager.Verify(m => m.SetVariable("variable", 42));
        }

        #endregion

        #region 6 Jfalse

        [Test]
        public void TheJneCommandMovesTheScriptPointerWhenTheBottomOfTheValueStackIsZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.Jfalse);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(42);
        }

        [Test]
        public void TheJneCommandDoesNotMoveTheScriptPointerWhenTheBottomOfTheValueStackIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(1);
            _script.AddCommand(ScriptToken.Jfalse);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(0);
        }

        #endregion

        #region 7 Jtrue

        [Test]
        public void TheJtrueCommandMovesTheScriptPointerByTheDistanceMinus4WhenTheBottomOfTheValueStackIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(1);
            _script.AddCommand(ScriptToken.Jtrue);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(42 - 4);
        }

        [Test]
        public void TheJtrueCommandDoesNotMoveTheScriptPointerWhenTheBottomOfTheValueStackIsZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.Jtrue);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(0);
        }

        #endregion

        #region 8 Jall

        [Test]
        public void TheJallCommandMovesTheScriptPointerByTheSpecifiedDistance()
        {
            _script.AddCommand(ScriptToken.Jall);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(42);
        }

        #endregion

        #region 9 Add

        [Test]
        public void TheAddCommandCallsTheStackAddCommand()
        {
            _script.AddCommand(ScriptToken.Add);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Add());
        }

        #endregion

        #region 10 Subtract

        [Test]
        public void TheSubtractCommandCallsTheStackSubtractCommand()
        {
            _script.AddCommand(ScriptToken.Subtract);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Subtract());
        }

        #endregion

        #region 11 Multiply

        [Test]
        public void TheMultiplyCommandCallsTheStackMultiplyCommand()
        {
            _script.AddCommand(ScriptToken.Multiply);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Multiply());
        }

        #endregion

        #region 12 Divide

        [Test]
        public void TheDivideCommandCallsTheStackDevideCommand()
        {
            _script.AddCommand(ScriptToken.Divide);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Divide());
        }

        #endregion

        #region 13 Negate

        [Test]
        public void TheNegateCommandCallsTheStackNegateCommand()
        {
            _script.AddCommand(ScriptToken.Negate);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Negate());
        }

        #endregion

        #region 14 LogicalNot

        [Test]
        public void TheLogicalNotCommandCallsTheStackLogicalNotCommand()
        {
            _script.AddCommand(ScriptToken.LogicalNot);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.LogicalNot());
        }

        #endregion

        #region 15 lt

        [Test]
        public void TheLtCommandCallsTheStackLtCommand()
        {
            _script.AddCommand(ScriptToken.Lt);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Lt());
        }

        #endregion

        #region 16 gt

        [Test]
        public void TheGtCommandCallsTheStackGtCommand()
        {
            _script.AddCommand(ScriptToken.Gt);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Gt());
        }

        #endregion

        #region 17 Lte

        [Test]
        public void TheLteCommandCallsTheStackLteCommand()
        {
            _script.AddCommand(ScriptToken.Lte);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Lte());
        }

        #endregion

        #region 18 Gte

        [Test]
        public void TheGteCommandCallsTheStackGteCommand()
        {
            _script.AddCommand(ScriptToken.Gte);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Gte());
        }

        #endregion

        #region 19 VariableEquals

        [Test]
        public void TheEqualsCommandCallsTheStackEVariablequalsCommand()
        {
            _script.AddCommand(ScriptToken.VariableEquals);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.VariableEquals());
        }

        #endregion

        #region 20 LogicalAnd

        [Test]
        public void TheLogicalAndCommandCallsTheStackLogicalOrCommand()
        {
            _script.AddCommand(ScriptToken.LogicalAnd);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.LogicalAnd());
        }

        #endregion

        #region 21 LogicalOr

        [Test]
        public void TheLogicalOrCommandCallsTheStackLogicalOrCommand()
        {
            _script.AddCommand(ScriptToken.LogicalOr);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.LogicalOr());
        }

        #endregion

        #region 22 Call Fn Routine

        [Test]
        public void TheCallFnRoutineCommandCallsTheFnRoutine()
        {
            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddIntValue(0);
            _script.AddString("fn routine");

            TerminateScriptAndRunScriptInterpreter();

            _mockFnRoutinesCaller.Verify(m => m.CallFnRoutine(_mockLocalVariableManager.Object, "fn routine", It.Is<List<object>>(l => l.Count == 0)));
        }

        [Test]
        public void TheCallFnRoutineCommandRequestsRequiredParametersFromTheStack()
        {
            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddIntValue(3);
            _script.AddString("fn routine");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PopValues(3));
        }

        [Test]
        public void TheCallFnRoutineCommandRequestsNoParametersFromTheStackWhenNoneRequired()
        {
            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddCommand(0);
            _script.AddString("fn routine");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PopValues(It.IsAny<int>()), Times.Never);
        }

        [Test]
        public void TheCallFnRoutineCommandPassesTheParametersPoppedOffTheStack()
        {
            var parameters = new List<object> {1, 2, 3};
            _mockValueStack.Setup(m => m.PopValues(3)).Returns(parameters);

            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddIntValue(3);
            _script.AddString("fn routine");

            TerminateScriptAndRunScriptInterpreter();

            _mockFnRoutinesCaller.Verify(m => m.CallFnRoutine(_mockLocalVariableManager.Object, "fn routine", parameters));
        }

        [Test]
        public void AfterCallingTheFnRoutineCommandTheReturnValueIsPlacedOnTheStack()
        {
            _mockFnRoutinesCaller.Setup(m =>
                m.CallFnRoutine(_mockLocalVariableManager.Object, "fn routine", It.IsAny<List<object>>())).Returns(42);

            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddIntValue(0);
            _script.AddString("fn routine");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 23 DropStackValue

        [Test]
        public void TheDropStackValuePopsTheBottomValueOfTheStack()
        {
            _script.AddCommand(ScriptToken.DropStackValue);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PopValue());
        }

        [Test]
        public void DropStackValuePausesScriptProcessingIfTheValueOnTheStackIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(1);
            _script.AddCommand(ScriptToken.DropStackValue);
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(It.IsAny<int>()), Times.Never);
        }

        [Test]
        public void DropStackValueDoesNotPauseScriptProcessingIfTheValueOnTheStackIsZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.DropStackValue);
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 24 End Script

        [Test]
        public void TheEndScriptCommandTerminatesTheScriptCleanly()
        {
            _script.AddCommand(ScriptToken.EndScript);

            RunScriptInterpreter();
        }

        [Test]
        public void IfAScriptRunsToTheEndWithNoEndScriptAnExceptionIsThrown()
        {
            Action act = () => RunScriptInterpreter();

            act.Should().Throw<Exception>().WithMessage("Unexpected end of script found in 'Script Name'");
        }

        #endregion

        #region 25 Drop Skip Pause Not Zero

        [Test]
        public void TestDropSkipPauseNotZeroPopsTheBottomValueFromTheStack()
        {
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PopValue());

        }

        #region ScriptReturn.Continue

        [Test]
        public void TestDropSkipPauseDoesNotUpdateProgramPositionForScriptReturnContinue()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns((int)ScriptReturn.Continue);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(0);
        }

        [Test]
        public void TestDropSkipPauseDoesNotPauseForScriptReturnContinue()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns((int)ScriptReturn.Continue);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);
            _script.AddCommand(ScriptToken.Divide);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Divide());
        }

        #endregion

        #region ScriptReturn.PauseRepeat

        [Test]
        public void TestDropSkipPauseUpdatesProgramPositionForScriptReturnPauseRepeat()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns((int)ScriptReturn.PauseRepeat);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(42 - 4);
        }

        [Test]
        public void TestDropSkipPauseDoesPauseForScriptReturnPauseRepeat()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns((int)ScriptReturn.PauseRepeat);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);
            _script.AddCommand(ScriptToken.Divide);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Divide(), Times.Never);
        }

        #endregion

        #region ScriptReturn.Pause

        [Test]
        public void TestDropSkipPauseDoesNotUpdatesProgramPositionForScriptReturnPause()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns((int)ScriptReturn.Pause);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _script.JumpDistance.Should().Be(0);
        }

        [Test]
        public void TestDropSkipPauseDoesPauseForScriptReturnPause()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns((int)ScriptReturn.Pause);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);
            _script.AddCommand(ScriptToken.Divide);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.Divide(), Times.Never);
        }

        #endregion

        #endregion

        #region 26 End Script

        [Test]
        public void ThePauseCommandPausesTheScript()
        {
            _script.AddCommand(ScriptToken.PauseScript);
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42), Times.Never);
        }

        [Test]
        public void AfterThePauseCommandTheScriptResumesWhereItLeftOff()
        {
            _script.AddCommand(ScriptToken.PauseScript);
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            TerminateScriptAndRunScriptInterpreter();
            RunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 27 Push Local Variable

        [Test]
        public void ThePushLocalVariableFetchesTheVariableValueFromTheLocalVariableManager()
        {
            _script.AddCommand(ScriptToken.PushLocalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockLocalVariableManager.Verify(m => m.GetVariable("variable"));
        }

        [Test]
        public void ThePushLocalVariablePushesTheLocalVariableValueOnToTheStack()
        {
            _mockLocalVariableManager.Setup(m => m.GetVariable("variable")).Returns(42);

            _script.AddCommand(ScriptToken.PushLocalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 28 Pop Local Variable

        [Test]
        public void ThePopLocalVariableCommandPopsTheBottomValueOfTheStack()
        {
            _script.AddCommand(ScriptToken.PopLocalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockValueStack.Verify(m => m.PopValue());
        }

        [Test]
        public void ThePopLocalVariableCommandSetsALocalVariableWithTheBottomValueOfTheStack()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(42);

            _script.AddCommand(ScriptToken.PopLocalVariable);
            _script.AddString("variable");

            TerminateScriptAndRunScriptInterpreter();

            _mockLocalVariableManager.Verify(m => m.SetVariable("variable", 42));
        }

        #endregion

        #region Supporting Code

        [SetUp]
        protected virtual void SetUp()
        {
            SetUpFnParameters();
            SetUpMocks();
            SetUpExpectations();
            SetUpScriptAndInterpreter();
        }

        void SetUpFnParameters()
        {
            _fnParamaters = new List<object>
            {
                1,
                2,
                3
            };
        }

        void SetUpMocks()
        {
            _mockValueStack = new Mock<IValueStack>();
            _mockFnRoutinesCaller = new Mock<IFnRoutinesCaller>();
            _mockGlobalVariableManager = new Mock<IVariableManager>();
            _mockLocalVariableManager = new Mock<IVariableManager>();
        }

        void SetUpExpectations()
        {
            _mockValueStack.Setup(m => m.PopValues(3)).Returns(_fnParamaters);
        }

        void SetUpScriptAndInterpreter()
        {
            _script = new MockSingleScript();
            _interpreter = new ScriptInterpreter(
                _mockFnRoutinesCaller.Object, _mockGlobalVariableManager.Object, _mockValueStack.Object);
        }

        void TerminateScriptAndRunScriptInterpreter()
        {
            _script.AddCommand(ScriptToken.EndScript);
            RunScriptInterpreter();
        }

        void RunScriptInterpreter()
        {
            _interpreter.Run(_script, _mockLocalVariableManager.Object);
        }


        #endregion
    }
}