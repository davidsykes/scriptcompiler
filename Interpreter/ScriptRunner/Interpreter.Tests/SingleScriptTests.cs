using System.Text;
using FluentAssertions;
using NUnit.Framework;

namespace Interpreter.Tests
{
    [TestFixture]
    public class SingleScriptTests
    {
        [Test]
        public void SingleScriptNameReturnsNameOfScript()
        {
            var script = new SingleScript("Script Name", Encoding.ASCII.GetBytes("Hello World"));

            script.Name.Should().Be("Script Name");
        }

        [Test]
        public void GetScriptDataReturnsTheDataPassedToTheConstructor()
        {
            var script = new SingleScript("Script Name", Encoding.ASCII.GetBytes("Hello World"));

            Encoding.UTF8.GetString(script.GetScriptBinary()).Should().Be("Hello World");
        }
        
    }
}
