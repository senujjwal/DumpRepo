using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Security.Cryptography;

namespace Hash
{
    class Program
    {
        static void Main(string[] args)
        {
            List<byte> plaintext = File.ReadAllBytes(@"E:\probfile.mp4").ToList();
            
            List<byte> lastBlock = plaintext.GetRange(plaintext.Count - plaintext.Count % 1024, plaintext.Count % 1024);
            plaintext = plaintext.GetRange(0, plaintext.Count - plaintext.Count % 1024);
            List<byte> hash = SHA256(lastBlock);

            while (plaintext.Count > 0)
            {
                lastBlock = plaintext.GetRange(plaintext.Count - 1024, 1024);
                lastBlock.AddRange(hash);
                hash = SHA256(lastBlock);
                plaintext.RemoveRange(plaintext.Count - 1024, 1024);
            }

            Console.WriteLine(ByteArrayToString(hash));
            Console.Read();
        }

        private static List<byte> SHA256(List<byte> Text)
        {
            MemoryStream mStream = new MemoryStream(Text.ToArray());
            SHA256 mySHA256 = SHA256Managed.Create();
            byte[] hashValue = mySHA256.ComputeHash(mStream);
            return hashValue.ToList();
        }

        private static string ByteArrayToString(List<byte> ba)
        {
            StringBuilder hex = new StringBuilder(ba.Count * 2);
            foreach(byte b in ba)
                hex.AppendFormat("{0:x2}", b);
            return hex.ToString();
        }
    }
}
