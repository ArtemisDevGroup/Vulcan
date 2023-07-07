using ManagedVulcanCore;

namespace VulcanTest
{
    internal class Program
    {
        static void Main(string[] args)
        {
            using (var managed_Stream = new ManagedFStream(@"C:\Users\Lungu\Desktop\datapc64_merged_set01_bnk_014818030_textures0.forge"))
            {
                using (var managed_forge = new ManagedForge(managed_Stream))
                {
                    for (int i = 0; i < managed_forge.entries.Length; i++)
                    {
                        Console.WriteLine("0x{0:X} - {1}", managed_forge.entries[i].Uid, managed_forge.entryMetadatas[i].Name);
                    }
                }
            }
        }
    }
}