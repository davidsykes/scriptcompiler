using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Interpreter
{
    public class SingleScript : ISingleScript
    {
        byte[] _scriptData;
        readonly BinaryReader _binaryReader;

        public SingleScript(byte[] scriptData)
        {
            _scriptData = scriptData;
            var memoryStream = new MemoryStream(_scriptData);
            _binaryReader = new BinaryReader(memoryStream);
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

        public byte[] GetScriptBinary()
        {
            return _scriptData;
        }

        public bool Eof => _binaryReader.BaseStream.Position >= _binaryReader.BaseStream.Length;
    }
}
