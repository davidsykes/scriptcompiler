using System.Text;
using FluentAssertions;
using NUnit.Framework;

namespace Interpreter.Tests
{
    [TestFixture]
    public class SingleScriptTests
    {

        [Test]
        public void GetScriptDataReturnsTheDataPassedToTheConstructor()
        {
            var script = new SingleScript(Encoding.ASCII.GetBytes("Hello World"));

            Encoding.UTF8.GetString(script.GetScriptBinary()).Should().Be("Hello World");
        }
        
    }
}
