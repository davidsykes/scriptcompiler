using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Interpreter
{
    public class ScriptLoader
    {
        public static Dictionary<string, SingleScript> LoadScripts(BinaryReader scriptsData)
        {
            var scriptCount = scriptsData.ReadInt32();

            var scripts = new Dictionary<string, SingleScript>();

            for (var script = 1; script <= scriptCount; script += 1)
                AddScript(scripts, scriptsData);

            return scripts;
        }

        static void AddScript(IDictionary<string, SingleScript> scripts, BinaryReader scriptsData)
        {
            var nameLength = scriptsData.ReadInt32();
            var scriptName = Encoding.UTF8.GetString(scriptsData.ReadBytes(nameLength));

            var scriptLength = scriptsData.ReadInt32();
            var scriptData = scriptsData.ReadBytes(scriptLength);

            scripts[scriptName] = new SingleScript(scriptData);
        }
    }
}
