using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace crypto_WEP
{
    class RC4 
    {
    void swap (int a, int b)
    {
        int t;
        t = a;
        a = b;
        b = t;
    }
        int[] S;
        RC4(int[] Key, int Keylength)
        {
            int i, j = 0;
            for (i = 0; i < 256; i++)
            {
                S[i] = i;
            }
            for (i = 0; i < 256; i++)
            {
                j = (j + S[i] + Key[i % Keylength] ) % 256;
                swap(S[i], S[j]);
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {

        }
    }
}
