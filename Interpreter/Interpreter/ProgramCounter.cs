using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Interpreter
{
    public class ProgramCounter : IProgramCounter
    {
        MemoryStream _memoryStream;
        readonly BinaryReader _binaryReader;

        public ProgramCounter(SingleScript script)
        {
            _memoryStream = new MemoryStream(script.GetScriptBinary());
            _binaryReader = new BinaryReader(_memoryStream);
        }

        public int GetCommand()
        {
            return _binaryReader.ReadInt32();
        }

        public int GetInteger()
        {
            return _binaryReader.ReadInt32();
        }

        public string GetLengthPrefixedString()
        {
            var stringLength = _binaryReader.ReadInt32();
            var scriptName = Encoding.UTF8.GetString(_binaryReader.ReadBytes(stringLength));
            return scriptName;
        }

        public string GetNullTerminatedString()
        {
            var stringData = new List<byte>();
            var byteValue = _binaryReader.ReadByte();
            while (byteValue > 0)
            {
                stringData.Add(byteValue);
                byteValue = _binaryReader.ReadByte();
            }
            return Encoding.UTF8.GetString(stringData.ToArray());
        }

        public long PC => _memoryStream.Position;

        public void MoveScriptPointer(int distance)
        {
            if (_memoryStream.Position + distance > _memoryStream.Length)
                throw new Exception("An attempt was made to move script pointer beyond the end of the script");

            _memoryStream.Seek(distance, SeekOrigin.Current);
        }

        public bool Eof => _binaryReader.BaseStream.Position >= _binaryReader.BaseStream.Length;
    }
}
