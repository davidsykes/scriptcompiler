﻿using FluentAssertions;
using System.Text;

#nullable disable
namespace Interpreter.Tests
{
    [TestFixture]
    public class ProgramCounterTests
    {
        IProgramCounter _programCounter;

        [Test]
        public void CallingGetCommandWhenNoScriptHasBeenSetUpThrowsAnException()
        {
            var programCounter = new ProgramCounter();

            Action act = () => programCounter.GetCommand();

            act.Should().Throw<Exception>()
                .WithMessage("Program Counter does not have a script.");
        }

        [Test]
        public void CallingGetIntegerWhenNoScriptHasBeenSetUpThrowsAnException()
        {
            var programCounter = new ProgramCounter();

            Action act = () => programCounter.GetInteger();

            act.Should().Throw<Exception>()
                .WithMessage("Program Counter does not have a script.");
        }

        [Test]
        public void CallingMoveScriptWhenNoScriptHasBeenSetUpThrowsAnException()
        {
            var programCounter = new ProgramCounter();

            Action act = () => programCounter.MoveScriptPointer(2);

            act.Should().Throw<Exception>()
                .WithMessage("Program Counter does not have a script.");
        }

        [Test]
        public void GetScriptNameReturnsNoScriptWhenNoScriptIsSet()
        {
            var programCounter = new ProgramCounter();

            programCounter.GetScriptName().Should().Be("No Script");
        }

        [Test]
        public void GetScriptNameReturnsScriptWhenScriptIsSet()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(0);
            });
            _programCounter.GetScriptName().Should().Be("Script Name");
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

            _programCounter.GetCommand().Should().Be(65);
            _programCounter.GetCommand().Should().Be(3);
            _programCounter.GetCommand().Should().Be(14);
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

            _programCounter.GetInteger().Should().Be(65);
            _programCounter.GetInteger().Should().Be(3);
            _programCounter.GetInteger().Should().Be(14);
        }

        [Test]
        public void GetLengthPrefixedStringReturnsTheNextLengthPrefixedStringInTheScriptData()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(11);
                bw.Write(Encoding.ASCII.GetBytes("Hello World"));
            });

            _programCounter.GetLengthPrefixedString().Should().Be("Hello World");
        }

        [Test]
        public void GetNullTerminatedtringReturnsTheNextNullTerminatedStringInTheScriptData()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(Encoding.ASCII.GetBytes("Hello World"));
                bw.Write((byte)0);
            });

            _programCounter.GetNullTerminatedString().Should().Be("Hello World");
        }

        [Test]
        public void TheEofPropertyDetectsTheEndOfTheScript()
        {
            SetUpScriptData(bw =>
            {
                bw.Write(65);
            });

            _programCounter.Eof.Should().BeFalse();

            _programCounter.GetCommand();

            _programCounter.Eof.Should().BeTrue();
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

            _programCounter.GetInteger().Should().Be(1);
            _programCounter.MoveScriptPointer(4);
            _programCounter.GetInteger().Should().Be(3);
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

            _programCounter.GetInteger().Should().Be(1);
            _programCounter.GetInteger().Should().Be(2);
            _programCounter.GetInteger().Should().Be(3);
            _programCounter.MoveScriptPointer(-8);
            _programCounter.GetInteger().Should().Be(2);
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

            Action act = () => _programCounter.MoveScriptPointer(13);

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

            Action act = () => _programCounter.MoveScriptPointer(-1);

            act.Should().Throw<Exception>()
                .WithMessage("An attempt was made to move the position before the beginning of the stream.");
        }

        #region Supporting Code

        void SetUpScriptData(Action<BinaryWriter> action)
        {
            var memoryStream = new MemoryStream();
            var bw = new BinaryWriter(memoryStream);

            action(bw);

            _programCounter = new ProgramCounter();
            _programCounter.SetScript(new SingleScript("Script Name", memoryStream.ToArray()));
        }
        
        #endregion
    }
}
