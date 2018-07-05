using System;
using System.IO;
using System.Text;
using FluentAssertions;
using NUnit.Framework;

namespace Interpreter.Tests
{
    [TestFixture]
    public class ProgramCounterTests
    {
        IProgramCounter _script;

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

        [Test]
        public void TheMoveScriptPointerCommandMovesTheScriptPointerByTheSpecifiedDistance()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(1);
                bw.Write(2);
                bw.Write(3);
            });

            _script.GetInteger().Should().Be(1);
            _script.MoveScriptPointer(4);
            _script.GetInteger().Should().Be(3);
        }

        [Test]
        public void TheMoveScriptPointerCommandMovesTheScriptPointerBackWhenTheDistanceIsNegative()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(1);
                bw.Write(2);
                bw.Write(3);
            });

            _script.GetInteger().Should().Be(1);
            _script.GetInteger().Should().Be(2);
            _script.GetInteger().Should().Be(3);
            _script.MoveScriptPointer(-8);
            _script.GetInteger().Should().Be(2);
        }

        [Test]
        public void TheMoveScriptPointerCommandThrowsAnExceptionWhenTheDistanceIsBeyondEndOfTheScript()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(1);
                bw.Write(2);
                bw.Write(3);
            });

            Action act = () => _script.MoveScriptPointer(13);

            act.Should().Throw<Exception>().WithMessage("An attempt was made to move script pointer beyond the end of the script");
        }

        [Test]
        public void TheMoveScriptPointerCommandThrowsAnExceptionWhenTheDistanceIsBeforeTheBeginningOfTheScript()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(1);
                bw.Write(2);
                bw.Write(3);
            });

            Action act = () => _script.MoveScriptPointer(-1);

            act.Should().Throw<Exception>()
                .WithMessage("An attempt was made to move the position before the beginning of the stream.");
        }

        #region Supporting Code

        void SetUpScriptData(Action<BinaryWriter> action)
        {
            var memoryStream = new MemoryStream();
            var bw = new BinaryWriter(memoryStream);

            action(bw);

            _script = new ProgramCounter(new SingleScript(memoryStream.ToArray()));
        }
        
        #endregion
    }
}
