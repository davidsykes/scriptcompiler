using FluentAssertions;
using NUnit.Framework;
using System;

namespace Interpreter.Tests
{
    [TestFixture]
    public class ValueStackTests
    {
        IValueStack _stack;

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
        public void TheVariableEqualsCommandThrowsAnExceptionWhenThereAreInsufficientValuesToVariableEquals()
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