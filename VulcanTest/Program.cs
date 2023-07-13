using ManagedVulcanCore;
using System.Diagnostics;
using System.Text;

namespace VulcanTest
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var watch = new Stopwatch();
            watch.Start();

            using (var managed_Stream = new ManagedFStream(@"C:\Users\Lungu\Desktop\datapc64_merged_set01_bnk_014818030_textures0.forge"))
            {
                using (var managed_forge = new ManagedForge(managed_Stream))
                {
                    var res = managed_forge.ReadEntry(0x3DF910F780);
                    return;
                    byte[] funnyArray = (byte[])(Array)res;
                    Console.WriteLine(funnyArray.Length);
                    
                    using (var stream = File.Open(@"C:\Users\Lungu\Desktop\test3.bin", FileMode.OpenOrCreate))
                    {
                        using (var writer = new BinaryWriter(stream, Encoding.UTF8, false))
                        {
                            writer.Write(funnyArray);
                        }
                    }
                    
                    /*
                    for (int i = 0; i < managed_forge.entries.Length; i++)
                    {
                        Console.WriteLine("0x{0:X} - {1}", managed_forge.entries[i].Uid, managed_forge.entryMetadatas[i].Name);
                    }
                    */
                }
            }

            watch.Stop();
            Console.WriteLine("VulcanTest Time Elapsed {0} ms", watch.Elapsed.TotalMilliseconds);
        }
    }
}