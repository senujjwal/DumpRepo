using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.IO;

namespace PaddingOracleAttack
{
    class Program
    {
        static Dictionary<string, DecryptionResponse> responseCache = new Dictionary<string,DecryptionResponse>();
        const string FileName = "cache.txt";
        static StreamWriter swrite;

        static void Main(string[] args)
        {
            StreamReader sread = new StreamReader(FileName);
            while (sread.Peek() != -1)
            {
                string key = sread.ReadLine();
                string val = sread.ReadLine();
                DecryptionResponse resp;
                Enum.TryParse(val, out resp);
                responseCache[key] = resp;
            }
            sread.Close();
            //swrite = new StreamWriter(FileName, true);

            string cipherText = "f20bdba6ff29eed7b046d1df9fb7000058b1ffb4210a580f748b4ac714c001bd4a61044426fb515dad3f21f18aa577c0bdf302936266926ff37dbf7035d5eeb4";
            List<byte> cipherTextBytes = GetBytesFromHexString(cipherText);
            int blockCount = cipherTextBytes.Count / 16;
            List<byte> plaintextBytes = new List<byte>(cipherTextBytes.Count);

            int j;
            for (j = 0; j < cipherTextBytes.Count; j++) plaintextBytes.Add(0);
            for (j = 0; j < 8; j++) plaintextBytes[plaintextBytes.Count - j - 1] = 9;
            //plaintextBytes[plaintextBytes.Count - (j++) - 1] = 101;

                for (int guessBlock = blockCount - 1; guessBlock > 0; guessBlock--)
                {
                    Console.WriteLine("Testing Block " + guessBlock);
                    int blocksToTrim = blockCount - guessBlock - 1;

                    for (int guessPosition = 1; guessPosition <= 16; guessPosition++)
                    {
                        Console.WriteLine("Testing Position " + guessPosition);
                        if (plaintextBytes[plaintextBytes.Count - blocksToTrim * 16 - guessPosition] != 0)
                        {
                            Console.WriteLine("Skipping Testing. Plaintext: "
                                + plaintextBytes[plaintextBytes.Count - blocksToTrim * 16 - guessPosition]);

                            continue;
                        }

                        //List<byte> bytesToQuery = new List<byte>();
                        int correctGuess = -1;

                        //Parallel.For(0, 256, (guess,loopstate) =>
                        for (int guess = 0; guess < 256; guess++)
                        {
                            Console.Write("\rGuessing " + guess);
                            if(guess == guessPosition) continue;

                            // Get the list of bytes to query
                            List<byte> bytesToQuery = cipherTextBytes.GetRange(0, cipherTextBytes.Count - blocksToTrim * 16);
                            //int flipPosition = bytesToQuery.Count - 16 - guessPosition;

                            for (int i = 0; i < guessPosition; i++)
                            {
                                bytesToQuery[bytesToQuery.Count - 16 - i - 1] ^= (byte)(guessPosition ^ plaintextBytes[bytesToQuery.Count - i - 1]);
                            }

                            bytesToQuery[bytesToQuery.Count - 16 - guessPosition] ^= (byte)guess;

                            DecryptionResponse result = MakeRequest(bytesToQuery);

                            if (result == DecryptionResponse.BadMessage || result == DecryptionResponse.Success)
                            {
                                // Guess is right
                                //if (guess >= 0x20 && guess <= 0x7E)
                                {
                                    correctGuess = guess;
                                    Console.WriteLine("\rGuess " + guess + " Successful!!!");
                                    //plaintextBytes[bytesToQuery.Count - guessPosition - blocksToTrim * 16] = (byte)guess;
                                    //loopstate.Stop();
                                }
                                guess = 1000;
                            }
                        }//);

                        if(correctGuess == -1) correctGuess = guessPosition;
                        plaintextBytes[cipherTextBytes.Count - guessPosition - blocksToTrim * 16] = (byte)correctGuess;
                    }

                }

            // remove padding and iv
            int padding = plaintextBytes[plaintextBytes.Count-1];
            plaintextBytes.RemoveRange(plaintextBytes.Count - padding, padding);
            plaintextBytes.RemoveRange(0, 16);
            Console.WriteLine(Encoding.ASCII.GetString(plaintextBytes.ToArray()));
            Console.WriteLine("done");
            Console.Read();
            
        }

        enum DecryptionResponse
        {
            Success,    // 200 OK
            InvalidPad, // 403 Forbidden
            BadMessage, // 404 Not Found
        }

        private static DecryptionResponse MakeRequest(List<byte> TestArray)
        {
            string URL = "http://crypto-class.appspot.com/po?er=";
            string testString = GetHexString(TestArray);
            if (responseCache.ContainsKey(testString))
                return responseCache[testString];

            WebRequest req = WebRequest.Create(URL+testString);
            DecryptionResponse result;

            try
            {
                WebResponse resp = req.GetResponse();
                result = DecryptionResponse.Success;
            }
            catch (WebException ex)
            {                
                HttpStatusCode statusCode = ((HttpWebResponse)ex.Response).StatusCode;

                if (statusCode == HttpStatusCode.Forbidden)
                {
                    result = DecryptionResponse.InvalidPad;
                }
                else if (statusCode == HttpStatusCode.NotFound)
                {
                    result = DecryptionResponse.BadMessage;
                }
                else
                {
                    throw;
                }
            }

            swrite = new StreamWriter(FileName, true);
            responseCache[testString] = result;
            swrite.WriteLine(testString);
            swrite.WriteLine(result);
            swrite.Close();

            return result;
        }

        private static string GetHexString(List<byte> byteList)
        {
            StringBuilder sb = new StringBuilder();

            for (int j = 0; j < byteList.Count; j++)
            {
                sb.Append(byteList[j].ToString("X2"));
            }

            return sb.ToString();
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
