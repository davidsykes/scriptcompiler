using System.IO;
using System.Linq;
using System.Text;
using FluentAssertions;
using NUnit.Framework;

namespace Interpreter.Tests
{
    [TestFixture]
    public class ScriptLoaderTests
    {
        byte[] _script1;
        byte[] _script2;
        byte[] _script3;

        [Test]
        public void TheScriptLoaderLoadsSeveralScripts()
        {
            var data = CreateScriptFileWithSeveralScripts();

            var scripts = ScriptLoader.LoadScripts(data);

            scripts.Count.Should().Be(3);

            scripts.Keys.ToList().Should().BeEquivalentTo(2);   //{"Script 1","Script ","Script 3"});

            scripts["Script1"].Should().AllBeEquivalentTo(_script1);
            scripts["Script2"].Should().AllBeEquivalentTo(_script2);
            scripts["Script3"].Should().AllBeEquivalentTo(_script3);
        }


        #region Supporting Code

        byte[] CreateScriptFileWithSeveralScripts()
        {
            _script1 = Encoding.ASCII.GetBytes("One");
            _script2 = Encoding.ASCII.GetBytes("Two");
            _script3 = Encoding.ASCII.GetBytes("Three");

			var data = new MemoryStream();
            var writer = new BinaryWriter(data);

			writer.Write(3);

            WriteScript(writer, "Script 1", _script1);
            //WriteScript(writer, "Script 2", _script2);
            //WriteScript(writer, "Script 3", _script3);

            return data.GetBuffer();
        }

        static void WriteScript(BinaryWriter writer, string scriptName, byte[] scriptData)
        {
            writer.Write(scriptName.Length);
			writer.Write(Encoding.ASCII.GetBytes(scriptName));
			//writer.Write(scriptData.Length);
			//writer.Write(scriptData);
        }

        #endregion
    }
}
