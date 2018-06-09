using System;
using System.IO;
using System.Text;
using FluentAssertions;
using NUnit.Framework;

namespace Interpreter.Tests
{
    [TestFixture]
    public class SingeScriptTests
    {
        ISingleScript _script;

        [Test]
        public void GetScriptDataReturnsTheDataPassedToTheConstructor()
        {
            var script = new SingleScript(Encoding.ASCII.GetBytes("Hello World"));

            Encoding.UTF8.GetString(script.GetScriptBinary()).Should().Be("Hello World");
        }

        [Test]
        public void GetCommandReturnsTheNextCommandInTheScriptData()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(65);
                bw.Write(3);
                bw.Write(14);
            });

            _script.GetCommand().Should().Be(65);
            _script.GetCommand().Should().Be(3);
            _script.GetCommand().Should().Be(14);
        }

        [Test]
        public void GetIntegerReturnsTheNextIntegerInTheScriptData()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(65);
                bw.Write(3);
                bw.Write(14);
            });

            _script.GetInteger().Should().Be(65);
            _script.GetInteger().Should().Be(3);
            _script.GetInteger().Should().Be(14);
        }

        [Test]
        public void GetLengthPrefixedStringReturnsTheNextLengthPrefixedStringInTheScriptData()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(11);
                bw.Write(Encoding.ASCII.GetBytes("Hello World"));
            });

            _script.GetLengthPrefixedString().Should().Be("Hello World");
        }

        [Test]
        public void GetNullTerminatedtringReturnsTheNextNullTerminatedStringInTheScriptData()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(Encoding.ASCII.GetBytes("Hello World"));
                bw.Write((byte)0);
            });

            _script.GetNullTerminatedString().Should().Be("Hello World");
        }

        [Test]
        public void TheEofPropertyDetectsTheEndOfTheScript()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(65);
            });

            _script.Eof.Should().BeFalse();

            _script.GetCommand();

            _script.Eof.Should().BeTrue();
        }

        #region Supporting Code

        void SetUpScriptData(Action<BinaryWriter> action)
        {
            var memoryStream = new MemoryStream();
            var bw = new BinaryWriter(memoryStream);

            action(bw);

            _script = new SingleScript(memoryStream.ToArray());
        }
        
        #endregion
    }
}
