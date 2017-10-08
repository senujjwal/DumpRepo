using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;
using System.IO;


namespace BlockEncryptDecrypt
{
    class Program
    {
        static void Main(string[] args)
        {
            string keyString, cipherTextString;

            // Problem 1
            keyString = "140b41b22a29beb4061bda66b6747e14";
            cipherTextString = "4ca00ff4c898d61e1edbf1800618fb2828a226d160dad07883d04e008a7897ee2e4b7465d5290d0c0e6c6822236e1daafb94ffe0c5da05d9476be028ad7c1d81";
            CBCEncryption(keyString, cipherTextString);

            // Problem 2
            keyString = "140b41b22a29beb4061bda66b6747e14";
            cipherTextString = "5b68629feb8606f9a6667670b75b38a5b4832d0f26e1ab7da33249de7d4afc48e713ac646ace36e872ad5fb8a512428a6e21364b0c374df45503473c5242a253";
            CBCEncryption(keyString, cipherTextString);

            // Problem 3
            keyString = "36f18357be4dbd77f050515c73fcf9f2";
            cipherTextString = "69dda8455c7dd4254bf353b773304eec0ec7702330098ce7f7520d1cbbb20fc388d1b0adb5054dbd7370849dbf0b88d393f252e764f1f5f7ad97ef79d59ce29f5f51eeca32eabedd9afa9329";
            CTREncryption(keyString, cipherTextString);

            // Problem 4
            keyString = "36f18357be4dbd77f050515c73fcf9f2";
            cipherTextString = "770b80259ec33beb2561358a9f2dc617e46218c0a53cbeca695ae45faa8952aa0e311bde9d4e01726d3184c34451";
            CTREncryption(keyString, cipherTextString);



            Console.Read();
        }

        private static void CTREncryption(string keyString, string cipherTextString)
        {
            List<byte> key = GetBytesFromHexString(keyString);
            List<byte> cipherText = GetBytesFromHexString(cipherTextString);

            List<byte> IV = cipherText.GetRange(0, 16); // Get first 16 bytes as IV
            cipherText = cipherText.GetRange(16, cipherText.Count - 16); // Rest of the bytes as actual ciphertext

            List<byte> plainText = PerformCTREncryptionOrDecryption(cipherText, key, IV);
            List<byte> sanityCipherText = PerformCTREncryptionOrDecryption(plainText, key, IV);

            string plainTextString = Encoding.ASCII.GetString(plainText.ToArray());

            Console.WriteLine("\n\nPlainTextString: " + plainTextString);

            Console.WriteLine("\nPlainText: ");
            OutputHexString(plainText);
            Console.WriteLine("CipherText: ");
            OutputHexString(cipherText);
            Console.WriteLine("SanityCipherText: ");
            OutputHexString(sanityCipherText);
        }

        private static void CBCEncryption(string keyString, string cipherTextString)
        {
            List<byte> key = GetBytesFromHexString(keyString);
            List<byte> cipherText = GetBytesFromHexString(cipherTextString);

            List<byte> IV = cipherText.GetRange(0, 16); // Get first 16 bytes as IV
            cipherText = cipherText.GetRange(16, cipherText.Count - 16); // Rest of the bytes as actual ciphertext

            List<byte> plainText = PerformCBCDecryption(cipherText, key, IV);
            List<byte> sanityCipherText = PerformCBCEncryption(plainText, key, IV);

            string plainTextString = Encoding.ASCII.GetString(plainText.ToArray());

            Console.WriteLine("\n\nPlainTextString: " + plainTextString);

            Console.WriteLine("\nPlainText: ");
            OutputHexString(plainText);
            Console.WriteLine("CipherText: ");
            OutputHexString(cipherText);
            Console.WriteLine("SanityCipherText: ");
            OutputHexString(sanityCipherText);
        }

        private static void OutputHexString(List<byte> byteList)
        {
            for (int j = 0; j < byteList.Count; j++)
            {
                Console.Write(byteList[j].ToString("X2"));
            }
                
            Console.WriteLine();
        }

        private static List<byte> PerformCTREncryptionOrDecryption(List<byte> cipherText, List<byte> key, List<byte> IV)
        {
            List<byte> plainText = new List<byte>();
            List<byte> currentCTBlock;
            List<byte> currentXORBlock;
            List<byte> currentCtr = IV.ToList();

            // For all ciphertext blocks
            for (int i = 0; i < cipherText.Count; i += 16)
            {
                if (cipherText.Count >= i + 16)
                {
                    currentCTBlock = cipherText.GetRange(i, 16);
                }
                else
                {
                    currentCTBlock = cipherText.GetRange(i, cipherText.Count - i);
                }

                currentXORBlock = EncryptOrDecryptBlockWithAES(currentCtr, key, true);
                
                // XOR with the 
                for (int j = 0; j < currentCTBlock.Count; j++)
                {
                    plainText.Add((byte)(currentXORBlock[j] ^ currentCTBlock[j]));
                }

                // Increment the CTR
                int pos = 15;
                do
                {
                    currentCtr[pos]++;
                    if (currentCtr[pos] != 0)
                        break;

                    pos--;
                } while (true);

            }

            return plainText;
        }

        private static List<byte> PerformCBCDecryption(List<byte> cipherText, List<byte> key, List<byte> IV)
        {
            List<byte> currentOutputBlock;
            List<byte> plainText = new List<byte>();

            List<byte> currentCTBlock;
            List<byte> prevCTBlock = IV.ToList();

            // For All Ciphertext Blocks
            for (int i = 0; i < cipherText.Count; i += 16)
            {
                currentCTBlock = cipherText.GetRange(i, 16);
                currentOutputBlock = EncryptOrDecryptBlockWithAES(currentCTBlock, key, false);

                // XOR current output block with the previous CT block
                for (int j = 0; j < 16; j++)
                {
                    currentOutputBlock[j] = (byte)(currentOutputBlock[j] ^ prevCTBlock[j]);
                }

                prevCTBlock = currentCTBlock;
                plainText.AddRange(currentOutputBlock);
            }

            // Remove the padding
            int paddingCount = plainText[plainText.Count - 1];
            plainText.RemoveRange(plainText.Count - paddingCount, paddingCount);

            return plainText;
        }

        private static List<byte> PerformCBCEncryption(List<byte> plainText, List<byte> key, List<byte> IV)
        {
            List<byte> currentPlainTextBlock; 
            List<byte> cipherText = new List<byte>();

            // First output IV to CipherText
            List<byte> currentOutputBlock = IV.ToList();

            // For all plaintext blocks
            for (int i = 0; i < plainText.Count; i += 16)
            {
                // Loop for all 16-byte blocks in PT
                if (plainText.Count >= i + 16)
                {
                    // We have one full block of PT
                    currentPlainTextBlock = plainText.GetRange(i, 16);
                }
                else
                {
                    // We have a partial block
                    currentPlainTextBlock = plainText.GetRange(i, plainText.Count - i);

                    // Add Padding
                    for (int j = 0; j < (16 - (plainText.Count - i)); j++)
                    {
                        currentPlainTextBlock.Add((byte)j);
                    }
                }

                // XOR current plaintext block with the previous output block
                for (int j = 0; j < 16; j++)
                {
                    currentPlainTextBlock[j] = (byte)(currentOutputBlock[j] ^ currentPlainTextBlock[j]);
                }

                currentOutputBlock = EncryptOrDecryptBlockWithAES(currentPlainTextBlock, key, true); 
                cipherText.AddRange(currentOutputBlock);
            }

            // We have complete blocks. Add one more block
            if (plainText.Count % 16 == 0)
            {
                currentPlainTextBlock = new List<byte>();
                for (int j = 0; j < 16; j++)
                {
                    currentPlainTextBlock.Add((byte)(currentOutputBlock[j] ^ 16));
                }

                currentOutputBlock = EncryptOrDecryptBlockWithAES(currentPlainTextBlock, key, true);
                cipherText.AddRange(currentOutputBlock);
            }

            return cipherText;
        }

        private static List<byte> EncryptOrDecryptBlockWithAES(List<byte> Block, List<byte> Key, bool PerformEncryption)
        {
            // Initialize AES
            AesCryptoServiceProvider myAes = new AesCryptoServiceProvider();
            myAes.BlockSize = 128;
            myAes.Key = Key.ToArray();
            myAes.Mode = CipherMode.ECB; // ECB since we are implementing modes manually
            myAes.Padding = PaddingMode.None;

            ICryptoTransform transformer;
            if (PerformEncryption)
            {
                transformer = myAes.CreateEncryptor();
            }
            else
            {
                transformer = myAes.CreateDecryptor();
            }

            using (MemoryStream msStream = new MemoryStream())
            {
                using (CryptoStream cStream = new CryptoStream(msStream, transformer, CryptoStreamMode.Write))
                {
                    cStream.Write(Block.ToArray(), 0, Block.Count);
                    cStream.Flush();
                    return msStream.ToArray().ToList();
                }
            }
        }

        private static List<byte> GetBytesFromHexString(string str)
        {
            return Enumerable.Range(0, str.Length)
                .Where(x => x % 2 == 0)
                .Select(x => Convert.ToByte(str.Substring(x, 2), 16))
                .ToList();
        }
    }
}
