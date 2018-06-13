using FluentAssertions;
using NUnit.Framework;

namespace Interpreter.Tests
{
    [TestFixture]
    public class VariableManagerTests
    {
        VariablesManager _variablesManager;

        [Test]
        public void GettingTheValueOfAnUnrecognisedVariableReturnsZero()
        {
            _variablesManager.GetVariable("unknown").Should().Be(0);
        }

        [Test]
        public void AValueCanBeSetAndRetrievedFromTheVariablesManager()
        {
            _variablesManager.SetVariable("var1", 42);

            _variablesManager.GetVariable("var1").Should().Be(42);
        }

        #region Supporting Code

        [SetUp]
        protected virtual void SetUp()
        {
            _variablesManager = new VariablesManager();
        }

        #endregion
    }
}