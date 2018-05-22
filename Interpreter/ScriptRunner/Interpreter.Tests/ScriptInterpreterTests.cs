
using System;
using System.IO;
using NUnit.Framework;
using FluentAssertions;

namespace Interpreter.Tests
{

    [TestFixture]

    public class ScriptInterpreterTests
    {
        [Test]
        public void CreatingAScriptInterpreterWithNullDataThrowsAnException()
        {
            // ReSharper disable once NotAccessedVariable
            IScriptInterpreter interpreter;

            Action act = () => interpreter = new ScriptInterpreter(null);

            act.Should().Throw<ArgumentNullException>();
        }

        [Test]
        public void RunningAScriptInterpreterWithEmptyScriptThrowsAnException()
        {
            IScriptInterpreter interpreter = new ScriptInterpreter(new MemoryStream());

            Action act = () => interpreter = new ScriptInterpreter(null);

            act.Should().Throw<ArgumentNullException>();
        }
    }
}
