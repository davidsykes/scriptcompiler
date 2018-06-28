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
        Mock<IValueStack> _mockValueStack;
        Mock<IFnRoutinesCaller> _mockFnRoutinesCaller;
        MockSingleScript _script;
        Mock<IVariableManager> _mockVariableManager;
        ScriptInterpreter _interpreter;
        List<object> _fnParamaters;

        #region Initialisation

        [Test]
        public void CreatingAScriptInterpreterWithNullScriptDataThrowsArgumentNullExceptionException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter("Script", null, _mockFnRoutinesCaller.Object, _mockVariableManager.Object, _mockValueStack.Object);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void CreatingAScriptInterpreterWithNullFnRoutineCallerThrowsArgumentNullExceptionException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter("Script", new MockSingleScript(), null, _mockVariableManager.Object, _mockValueStack.Object);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void CreatingAScriptInterpreterWithNullVariableManagerThrowsArgumentNullExceptionException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter("Script", new MockSingleScript(), _mockFnRoutinesCaller.Object, null, _mockValueStack.Object);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void CreatingAScriptInterpreterWithNullValueStackThrowsArgumentNullExceptionException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter("Script", new MockSingleScript(), _mockFnRoutinesCaller.Object, _mockVariableManager.Object, null);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void RunningAScriptWithAnInvalidInstructionThrowsAnException()
        {
            _script.AddIntValue(int.MaxValue);

            Action action = () => _interpreter.Run();

            action.Should().Throw<InvalidOperationException>().WithMessage("Invalid Script Command 2147483647");
        }

        #endregion

        #region 1 Push Int Value

        [Test]
        public void ThePushIntValueCommandPushesTheValueOnToTheStack()
        {
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            RunInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 3 Push String Value

        [Test]
        public void ThePushStringValueCommandPushesTheValueOnToTheStack()
        {
            _script.AddCommand(ScriptToken.PushStringValue);
            _script.AddString("gimmer");

            RunInterpreter();

            _mockValueStack.Verify(m => m.PushValue("gimmer"));
        }

        #endregion

        #region 4 Push Variable

        [Test]
        public void ThePushVariableFetchesTheVariableValueFromTheVariableManager()
        {
            _script.AddCommand(ScriptToken.PushVariable);
            _script.AddString("variable");

            RunInterpreter();

            _mockVariableManager.Verify(m => m.GetVariable("variable"));
        }

        [Test]
        public void ThePushVariablePushesTheVariableValueOnToTheStack()
        {
            _mockVariableManager.Setup(m => m.GetVariable("variable")).Returns(42);

            _script.AddCommand(ScriptToken.PushVariable);
            _script.AddString("variable");

            RunInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 5 Pop Variable

        [Test]
        public void ThePopVariableCommandPopsTheBottomValueOfTheStack()
        {
            _script.AddCommand(ScriptToken.PopVariable);
            _script.AddString("variable");

            RunInterpreter();

            _mockValueStack.Verify(m => m.PopValue());
        }

        [Test]
        public void ThePopVariableCommandSetsAVariableWithTheBottomValueOfTheStack()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(42);

            _script.AddCommand(ScriptToken.PopVariable);
            _script.AddString("variable");

            RunInterpreter();

            _mockVariableManager.Verify(m => m.SetVariable("variable", 42));
        }

        #endregion

        #region 6 Jfalse

        [Test]
        public void TheJneCommandMovesTheScriptPointerWhenTheBottomOfTheValueStackIsZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.Jfalse);
            _script.AddIntValue(42);

            RunInterpreter();

            _script.JumpDistance.Should().Be(42);
        }

        [Test]
        public void TheJneCommandDoesNotMoveTheScriptPointerWhenTheBottomOfTheValueStackIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(1);
            _script.AddCommand(ScriptToken.Jfalse);
            _script.AddIntValue(42);

            RunInterpreter();

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

            RunInterpreter();

            _script.JumpDistance.Should().Be(42 - 4);
        }

        [Test]
        public void TheJtrueCommandDoesNotMoveTheScriptPointerWhenTheBottomOfTheValueStackIsZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.Jtrue);
            _script.AddIntValue(42);

            RunInterpreter();

            _script.JumpDistance.Should().Be(0);
        }

        #endregion

        #region 8 Jall

        [Test]
        public void TheJallCommandMovesTheScriptPointerByTheSpecifiedDistance()
        {
            _script.AddCommand(ScriptToken.Jall);
            _script.AddIntValue(42);

            RunInterpreter();

            _script.JumpDistance.Should().Be(42);
        }

        #endregion

        #region 9 Add

        [Test]
        public void TheAddCommandCallsTheStackAddCommand()
        {
            _script.AddCommand(ScriptToken.Add);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Add());
        }

        #endregion

        #region 10 Subtract

        [Test]
        public void TheSubtractCommandCallsTheStackSubtractCommand()
        {
            _script.AddCommand(ScriptToken.Subtract);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Subtract());
        }

        #endregion

        #region 11 Multiply

        [Test]
        public void TheMultiplyCommandCallsTheStackMultiplyCommand()
        {
            _script.AddCommand(ScriptToken.Multiply);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Multiply());
        }

        #endregion

        #region 12 Divide

        [Test]
        public void TheDivideCommandCallsTheStackDevideCommand()
        {
            _script.AddCommand(ScriptToken.Divide);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Divide());
        }

        #endregion

        #region 13 Negate

        [Test]
        public void TheNegateCommandCallsTheStackNegateCommand()
        {
            _script.AddCommand(ScriptToken.Negate);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Negate());
        }

        #endregion

        #region 14 LogicalNot

        [Test]
        public void TheLogicalNotCommandCallsTheStackLogicalNotCommand()
        {
            _script.AddCommand(ScriptToken.LogicalNot);

            RunInterpreter();

            _mockValueStack.Verify(m => m.LogicalNot());
        }

        #endregion

        #region 15 lt

        [Test]
        public void TheLtCommandCallsTheStackLtCommand()
        {
            _script.AddCommand(ScriptToken.Lt);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Lt());
        }

        #endregion

        #region 16 gt

        [Test]
        public void TheGtCommandCallsTheStackGtCommand()
        {
            _script.AddCommand(ScriptToken.Gt);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Gt());
        }

        #endregion

        #region 17 Lte

        [Test]
        public void TheLteCommandCallsTheStackLteCommand()
        {
            _script.AddCommand(ScriptToken.Lte);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Lte());
        }

        #endregion

        #region 18 Gte

        [Test]
        public void TheGteCommandCallsTheStackGteCommand()
        {
            _script.AddCommand(ScriptToken.Gte);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Gte());
        }

        #endregion

        #region 19 VariableEquals

        [Test]
        public void TheEqualsCommandCallsTheStackEVariablequalsCommand()
        {
            _script.AddCommand(ScriptToken.VariableEquals);

            RunInterpreter();

            _mockValueStack.Verify(m => m.VariableEquals());
        }

        #endregion

        #region 21 LogicalOr

        [Test]
        public void TheLogicalOrCommandCallsTheStackLogicalOrCommand()
        {
            _script.AddCommand(ScriptToken.LogicalOr);

            RunInterpreter();

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

            RunInterpreter();

            _mockFnRoutinesCaller.Verify(m => m.CallFnRoutine("fn routine",
                It.Is<List<object>>(l => l.Count == 0)));
        }

        [Test]
        public void TheCallFnRoutineCommandRequestsRequiredParametersFromTheStack()
        {
            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddIntValue(3);
            _script.AddString("fn routine");

            RunInterpreter();

            _mockValueStack.Verify(m => m.PopValues(3));
        }

        [Test]
        public void TheCallFnRoutineCommandRequestsNoParametersFromTheStackWhenNoneRequired()
        {
            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddCommand(0);
            _script.AddString("fn routine");

            RunInterpreter();

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

            RunInterpreter();

            _mockFnRoutinesCaller.Verify(m => m.CallFnRoutine("fn routine", parameters));
        }

        [Test]
        public void AfterCallingTheFnRoutineCommandTheReturnValueIsPlacedOnTheStack()
        {
            _mockFnRoutinesCaller.Setup(m =>
                m.CallFnRoutine("fn routine", It.IsAny<List<object>>())).Returns(42);

            _script.AddCommand(ScriptToken.CallFnRoutine);
            _script.AddIntValue(0);
            _script.AddString("fn routine");

            RunInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 23 DropStackValue

        [Test]
        public void TheDropStackValuePopsTheBottomValueOfTheStack()
        {
            _script.AddCommand(ScriptToken.DropStackValue);

            RunInterpreter();

            _mockValueStack.Verify(m => m.PopValue());
        }

        [Test]
        public void DropStackValuePausesScriptProcessingIfTheValueOnTheStackIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(1);
            _script.AddCommand(ScriptToken.DropStackValue);
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            RunInterpreter();

            _mockValueStack.Verify(m => m.PushValue(It.IsAny<int>()), Times.Never);
        }

        [Test]
        public void DropStackValueDoesNotPauseScriptProcessingIfTheValueOnTheStackIsZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.DropStackValue);
            _script.AddCommand(ScriptToken.PushIntValue);
            _script.AddIntValue(42);

            RunInterpreter();

            _mockValueStack.Verify(m => m.PushValue(42));
        }

        #endregion

        #region 24 End Script

        [Test]
        public void TheEndScriptCommandTerminatesTheScriptCleanly()
        {
            _script.AddCommand(ScriptToken.EndScript);

            _interpreter.Run();
        }

        [Test]
        public void IfAScriptRunsToTheEndWithNoEndScriptAnExceptionIsThrown()
        {
            Action act = () => _interpreter.Run();

            act.Should().Throw<Exception>().WithMessage("Unexpected end of script found in 'Script'");
        }

        #endregion

        #region 25 Drop Skip Pause Not Zero

        [Test]
        public void TestDropSkipPauseNotZeroPopsTheBottomValueFromTheStack()
        {
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);

            RunInterpreter();

            _mockValueStack.Verify(m => m.PopValue());

        }

        [Test]
        public void TestDropSkipPauseNotZeroUpdatesProgramPositionWhenStackValueIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(1);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);

            RunInterpreter();

            _script.JumpDistance.Should().Be(42 - 4);
        }

        [Test]
        public void TestDropSkipPauseNotZeroDoesNotUpdateProgramPositionWhenStackValueIsZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);

            RunInterpreter();

            _script.JumpDistance.Should().Be(0);
        }

        [Test]
        public void TestDropSkipPauseNotZeroPausesTheScriptWhenStackValueIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(1);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);
            _script.AddCommand(ScriptToken.Divide);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Divide(), Times.Never);
        }

        [Test]
        public void TestDropSkipPauseNotZeroDoesNotPauseTheScriptWhenStackValueIsNotZero()
        {
            _mockValueStack.Setup(m => m.PopValue()).Returns(0);
            _script.AddCommand(ScriptToken.DropSkipPauseNotZero);
            _script.AddIntValue(42);
            _script.AddCommand(ScriptToken.Divide);

            RunInterpreter();

            _mockValueStack.Verify(m => m.Divide());
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
            _mockVariableManager = new Mock<IVariableManager>();
        }

        void SetUpExpectations()
        {
            _mockValueStack.Setup(m => m.PopValues(3)).Returns(_fnParamaters);
        }

        void SetUpScriptAndInterpreter()
        {
            _script = new MockSingleScript();
            _interpreter = new ScriptInterpreter("Script", _script, _mockFnRoutinesCaller.Object, _mockVariableManager.Object, _mockValueStack.Object);
        }

        void RunInterpreter()
        {
            _script.AddCommand(ScriptToken.EndScript);
            _interpreter.Run();
        }

        #endregion
    }
}