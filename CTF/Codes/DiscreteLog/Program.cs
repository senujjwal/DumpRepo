using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace DiscreteLog
{
    class Program
    {
        static void Main(string[] args)
        {
            string pStr = "13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171";
            string gStr = "11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568";
            string hStr = "3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333";

            BigInteger p, g, h;
            BigInteger.TryParse(pStr, out p);
            BigInteger.TryParse(gStr, out g);
            BigInteger.TryParse(hStr, out h);
            int B = 1;
            for (int i = 0; i < 20; i++) B *= 2;
            BigInteger gB = BigInteger.ModPow(g, B, p);

            Dictionary<BigInteger, int> hgx1invdict = new Dictionary<BigInteger, int>(B);
            Dictionary<BigInteger, int> gBx0Dict = new Dictionary<BigInteger, int>(B);
            int pt;

            BigInteger x0sol = 0, x1sol = 0;

            /*
            pt = -1;
            for(int x1 = 0; x1 < B; x1++)
            {
                BigInteger gx1 = BigInteger.ModPow(g, x1, p);
                BigInteger gx1_inverse = BigInteger.ModPow(gx1, p - 2, p);

                hgx1inv.Add((h * gx1_inverse) % p, x1);
                if(pt == 100 * x1 / B) continue;

                pt = 100 * x1 / B;
                Console.Write("\rInitializing Lookup Table: " + pt + "%");
            }

            Console.WriteLine();

            pt = -1;
            for (int x0 = 0; x0 < B; x0++)
            {
                BigInteger gBx0 = BigInteger.ModPow(gB, x0, p);

                if (hgx1inv.ContainsKey(gBx0))
                {
                    x0sol = x0;
                    x1sol = hgx1inv[gBx0];
                    break;
                }

                if (pt == 100*x0/B) continue;
                pt = 100*x0/B;
                Console.Write("\rSearching Lookup Table: " + pt + "%");
            }

             */
            Console.WriteLine("Initializing...");

            //pt = -1;
            //for(int x0 = 0; x0 < B; x0++)
            Parallel.For(0, B, x0 =>
            {
                gBx0Dict.Add(BigInteger.ModPow(gB, x0, p), x0);

                /*if (pt == 100*x0/B) continue;
                pt = 100*x0/B;
                Console.Write("\rInitializing Lookup Table: " + pt + "%");*/
            });

            Console.WriteLine();

            Console.WriteLine("Searching...");

            //pt = -1;
            //for(int x1 = 0; x1 < B; x1++)
            Parallel.For(0, B, (x1,loopstate) =>
            {
                BigInteger gx1 = BigInteger.ModPow(g, x1, p);
                BigInteger gx1_inverse = BigInteger.ModPow(gx1, p - 2, p);
                BigInteger hgx1inv = (h*gx1_inverse)%p;

                if (gBx0Dict.ContainsKey(hgx1inv))
                {
                    x0sol = gBx0Dict[hgx1inv];
                    x1sol = x1;
                    loopstate.Stop();
                }

                /*if (pt == 100*x1/B) continue;
                pt = 100*x1/B;
                Console.Write("\rSearching Lookup Table: " + pt + "%");*/
            });




            Console.WriteLine();

            Console.WriteLine(x0sol * B + x1sol);
            Console.WriteLine();
            Console.WriteLine((x0sol*B + x1sol)%p);

            Console.Read();

        }
    }
}
