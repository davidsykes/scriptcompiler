using FluentAssertions;
using NUnit.Framework;
using System;

namespace Interpreter.Tests
{
    [TestFixture]
    public class ValueStackTests
    {
        IValueStack _stack;

        #region Push and Pop

        [Test]
        public void AnIntegerCanBePushedAndPoppedOffTheStack()
        {
            _stack.PushValue(42);

            _stack.PopValue().Should().Be(42);
        }

        [Test]
        public void PoppingFromAnEmptyStackThrowsAnException()
        {
            Action act = () => _stack.PopValue();

            act.Should().Throw<StackOverflowException>();
        }

        [Test]
        public void IsEmptyReturnsTrueWhenTheStackIsEmpty()
        {
            _stack.PushValue(22);
            _stack.PopValue();

            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void IsEmptyReturnsFalseWhenTheStackIsNotEmpty()
        {
            _stack.PushValue(22);

            _stack.IsEmpty.Should().BeFalse();
        }

        [Test]
        public void ValuesArePoppedInReverseOrder()
        {
            _stack.PushValue(11);
            _stack.PushValue(22);
            _stack.PushValue(33);

            _stack.PopValue().Should().Be(33);
            _stack.PopValue().Should().Be(22);
            _stack.PopValue().Should().Be(11);
        }

        [Test]
        public void PopValuesPopsMultipleValuesOffTheStack()
        {
            _stack.PushValue(11);
            _stack.PushValue(22);
            _stack.PushValue(33);

            _stack.PopValues(3).Should().BeEquivalentTo(11,22,33);
        }

        [Test]
        public void PopValuesLeavesOtherValuesOnTheStack()
        {
            _stack.PushValue(11);
            _stack.PushValue(22);
            _stack.PushValue(33);

            _stack.PopValues(2).Should().BeEquivalentTo(22, 33);
            _stack.PopValue().Should().Be(11);
        }

        #endregion

        #region 9 Add

        [Test]
        public void TheAddCommandPopsTheTwoValuesAtTheBottomOfTheStackAddsThemAndPushesTheResult()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);

            _stack.Add();

            _stack.PopValue().Should().Be(46);
            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheAddCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(78);

            _stack.Add();

            _stack.PopValue().Should().Be(134);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheAddCommandThrowsAnExceptionWhenThereAreInsufficientValuesToAdd()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Add();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 10 Subtract

        [Test]
        public void TheSubtractCommandPopsTheTwoValuesAtTheBottomOfTheStackSubtractsThemAndPushesTheResult()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);

            _stack.Subtract();

            _stack.PopValue().Should().Be(-22);
            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheSubtractCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(78);

            _stack.Subtract();

            _stack.PopValue().Should().Be(-22);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheSubtractCommandThrowsAnExceptionWhenThereAreInsufficientValuesToSubtract()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Subtract();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 11 Multiply

        [Test]
        public void TheMultiplyCommandPopsTheTwoValuesAtTheBottomOfTheStackMultipliesThemAndPushesTheResult()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);

            _stack.Multiply();

            _stack.PopValue().Should().Be(408);
            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheMultiplyCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(78);

            _stack.Multiply();

            _stack.PopValue().Should().Be(4368);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheMultiplyCommandThrowsAnExceptionWhenThereAreInsufficientValuesToMultiply()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Multiply();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 12 Divide

        [Test]
        public void TheDivideCommandPopsTheTwoValuesAtTheBottomOfTheStackDividesThemAndPushesTheResult()
        {
            _stack.PushValue(36);
            _stack.PushValue(12);

            _stack.Divide();

            _stack.PopValue().Should().Be(3);
            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheDivideCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(8);

            _stack.Divide();

            _stack.PopValue().Should().Be(7);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheDivideCommandThrowsAnExceptionWhenThereAreInsufficientValuesToDivide()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Divide();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 13 Negate

        [Test]
        public void TheNegateCommandPopsTheValueAtTheBottomOfTheStackNegatesItAndPushesTheResult()
        {
            _stack.PushValue(12);

            _stack.Negate();

            _stack.PopValue().Should().Be(-12);
            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheNegateCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);

            _stack.Negate();

            _stack.PopValue().Should().Be(-56);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheNegateCommandThrowsAnExceptionWhenThereAreInsufficientValuesToNegate()
        {
            Action act = () => _stack.Negate();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 14 LogicalNot

        [Test]
        public void TheLogicalNotCommandPopsTheValueAtTheBottomOfTheStackLogicallyNotsItAndPushesTheResult()
        {
            _stack.PushValue(12);

            _stack.LogicalNot();

            _stack.PopValue().Should().Be(-13);
            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheLogicalNotCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);

            _stack.LogicalNot();

            _stack.PopValue().Should().Be(-57);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheLogicalNotCommandThrowsAnExceptionWhenThereAreInsufficientValuesToLogicallyNot()
        {
            Action act = () => _stack.LogicalNot();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 15 Lt

        [Test]
        public void TheLtCommandLeavesResult1WhenValue1IsLessThanValue2()
        {
            _stack.PushValue(1);
            _stack.PushValue(2);

            _stack.Lt();

            _stack.PopValue().Should().Be(1);
        }

        [Test]
        public void TheLtCommandLeavesResult0WhenValue1IsEqualToValue2()
        {
            _stack.PushValue(2);
            _stack.PushValue(2);

            _stack.Lt();

            _stack.PopValue().Should().Be(0);
        }

        [Test]
        public void TheLtCommandLeavesResult0WhenValue1IsGreaterThanValue2()
        {
            _stack.PushValue(3);
            _stack.PushValue(2);

            _stack.Lt();

            _stack.PopValue().Should().Be(0);
        }

        [Test]
        public void TheLtCommandCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(56);

            _stack.Lt();

            _stack.PopValue().Should().Be(0);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheLtCommandCommandThrowsAnExceptionWhenThereAreInsufficientValues()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Lt();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 16 Gt

        [Test]
        public void TheGtCommandLeavesResult0WhenValue1IsLessThanValue2()
        {
            _stack.PushValue(1);
            _stack.PushValue(2);

            _stack.Gt();

            _stack.PopValue().Should().Be(0);
        }

        [Test]
        public void TheGtCommandLeavesResult0WhenValue1IsEqualToValue2()
        {
            _stack.PushValue(2);
            _stack.PushValue(2);

            _stack.Gt();

            _stack.PopValue().Should().Be(0);
        }

        [Test]
        public void TheGtCommandLeavesResult1WhenValue1IsGreaterThanValue2()
        {
            _stack.PushValue(3);
            _stack.PushValue(2);

            _stack.Gt();

            _stack.PopValue().Should().Be(1);
        }

        [Test]
        public void TheGtCommandCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(56);

            _stack.Gt();

            _stack.PopValue().Should().Be(0);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheGtCommandCommandThrowsAnExceptionWhenThereAreInsufficientValues()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Gt();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 17 Lte

        [Test]
        public void TheLteCommandLeavesResult1WhenValue1IsLessThanValue2()
        {
            _stack.PushValue(1);
            _stack.PushValue(2);

            _stack.Lte();

            _stack.PopValue().Should().Be(1);
        }

        [Test]
        public void TheLteCommandLeavesResult1WhenValue1IsEqualToValue2()
        {
            _stack.PushValue(2);
            _stack.PushValue(2);

            _stack.Lte();

            _stack.PopValue().Should().Be(1);
        }

        [Test]
        public void TheLteCommandLeavesResult0WhenValue1IsGreaterThanValue2()
        {
            _stack.PushValue(3);
            _stack.PushValue(2);

            _stack.Lte();

            _stack.PopValue().Should().Be(0);
        }

        [Test]
        public void TheLteCommandCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(56);

            _stack.Lte();

            _stack.PopValue().Should().Be(1);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheLteCommandCommandThrowsAnExceptionWhenThereAreInsufficientValues()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Lte();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 18 gte

        [Test]
        public void TheGteCommandLeavesResult0WhenValue1IsLessThanValue2()
        {
            _stack.PushValue(1);
            _stack.PushValue(2);

            _stack.Gte();

            _stack.PopValue().Should().Be(0);
        }

        [Test]
        public void TheGteCommandLeavesResult1WhenValue1IsEqualToValue2()
        {
            _stack.PushValue(2);
            _stack.PushValue(2);

            _stack.Gte();

            _stack.PopValue().Should().Be(1);
        }

        [Test]
        public void TheGteCommandLeavesResult1WhenValue1IsGreaterThanValue2()
        {
            _stack.PushValue(3);
            _stack.PushValue(2);

            _stack.Gte();

            _stack.PopValue().Should().Be(1);
        }

        [Test]
        public void TheGteCommandCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(56);

            _stack.Gte();

            _stack.PopValue().Should().Be(1);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheGteCommandCommandThrowsAnExceptionWhenThereAreInsufficientValues()
        {
            _stack.PushValue(11);

            Action act = () => _stack.Gte();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion


        #region 19 VariableEquals

        [Test]
        public void TheVariableEqualsCommandPopsTheTwoValuesAtTheBottomOfTheStackVariableEqualsThemAndPushesTheResult()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.VariableEquals();
            _stack.PopValue().Should().Be(0);

            _stack.PushValue(12);
            _stack.PushValue(12);
            _stack.VariableEquals();
            _stack.PopValue().Should().Be(1);

            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheVariableEqualsCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(56);

            _stack.VariableEquals();

            _stack.PopValue().Should().Be(1);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheVariableEqualsCommandThrowsAnExceptionWhenThereAreInsufficientValues()
        {
            _stack.PushValue(11);

            Action act = () => _stack.VariableEquals();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region 21 LogicalOr

        [Test]
        public void TheLogicalOrCommandPopsTheTwoValuesAtTheBottomOfTheStackLogicalOrsThemAndPushesTheResult()
        {
            _stack.PushValue(0);
            _stack.PushValue(0);
            _stack.LogicalOr();
            _stack.PopValue().Should().Be(0);

            _stack.PushValue(0);
            _stack.PushValue(1);
            _stack.LogicalOr();
            _stack.PopValue().Should().Be(1);

            _stack.PushValue(2);
            _stack.PushValue(0);
            _stack.LogicalOr();
            _stack.PopValue().Should().Be(1);

            _stack.PushValue(3);
            _stack.PushValue(4);
            _stack.LogicalOr();
            _stack.PopValue().Should().Be(1);

            _stack.IsEmpty.Should().BeTrue();
        }

        [Test]
        public void TheLogicalOrCommandLeavesOtherValuesOnTheStackUnchanged()
        {
            _stack.PushValue(12);
            _stack.PushValue(34);
            _stack.PushValue(56);
            _stack.PushValue(78);

            _stack.LogicalOr();

            _stack.PopValue().Should().Be(1);
            _stack.PopValue().Should().Be(34);
            _stack.PopValue().Should().Be(12);
        }

        [Test]
        public void TheLogicalOrCommandThrowsAnExceptionWhenThereAreInsufficientValuesToLogicalOr()
        {
            _stack.PushValue(11);

            Action act = () => _stack.LogicalOr();

            act.Should().Throw<StackOverflowException>().WithMessage("Stack Underflow");
        }

        #endregion

        #region Supporting Code

        [SetUp]
        protected virtual void SetUp()
        {
            _stack = new ValueStack();
        }

        #endregion

    }
}