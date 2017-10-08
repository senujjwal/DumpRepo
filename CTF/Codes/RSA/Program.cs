using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;

namespace RSA
{
    class Program
    {
        static void Main(string[] args)
        {

            q4();

        }

        private static void q4()
        {
            string Nstr =
                "179769313486231590772930519078902473361797697894230657273430081157732675805505620686985379449212982959585501387537164015710139858647833778606925583497541085196591615128057575940752635007475935288710823649949940771895617054361149474865046711015101563940680527540071584560878577663743040086340742855278549092581";

            string Cstr =
                "22096451867410381776306561134883418017410069787892831071731839143676135600120538004282329650473509424343946219751512256465839967942889460764542040581564748988013734864120452325229320176487916666402997509188729971690526083222067771600019329260870009579993724077458967773697817571267229951148662959627934791540";

            string Pstr =
                "13407807929942597099574024998205846127479365820592393377723561443721764030073662768891111614362326998675040546094339320838419523375986027530441562135724301";

            string Qstr =
                "13407807929942597099574024998205846127479365820592393377723561443721764030073778560980348930557750569660049234002192590823085163940025485114449475265364281";

            string Estr = "65537";

            BigInteger N, C, P, Q ,E;
            BigInteger.TryParse(Nstr, out N);
            BigInteger.TryParse(Cstr, out C);
            BigInteger.TryParse(Pstr, out P);
            BigInteger.TryParse(Qstr, out Q);
            BigInteger.TryParse(Estr, out E);

            BigInteger phiN = (P - 1)*(Q - 1);
            BigInteger D = modInverse(E, phiN);
            BigInteger Pt = BigInteger.ModPow(C, D, N);

            Console.WriteLine(Pt.ToString("X"));
            
            

            Console.Read();
        }

        private static BigInteger modInverse(BigInteger a, BigInteger n)
        {
            BigInteger i = n, v = 0, d = 1;
            while(a > 0)
            {
                BigInteger t = i / a, x = a;
                a = i % x;
                i = x;
                x = d;
                d = v - t * x;
                v = x;
            }
            v %= n;
            if(v < 0) v = (v + n) % n;
            return v;
        }


        private static void q1()
        {
            string Nstr =
                    "179769313486231590772930519078902473361797697894230657273430081157732675805505620686985379449212982959585501387537164015710139858647833778606925583497541085196591615128057575940752635007475935288710823649949940771895617054361149474865046711015101563940680527540071584560878577663743040086340742855278549092581";
                //    "648455842808071669662824265346772278726343720706976263060439070378797308618081116462714015276061417569195587321840254520655424906719892428844841839353281972988531310511738648965962582821502504990264452100885281673303711142296421027840289307657458645233683357077834689715838646088239640236866252211790085787877";

            BigInteger N;
            BigInteger.TryParse(Nstr, out N);

            BigInteger A = Sqrt(N);
            BigInteger P, Q, x;

            bool result = false;
            do
            {
                A++;

                x = Sqrt(A * A - N);

                P = A - x;
                Q = A + x;

                if (P*Q == N)
                {
                    result = true;
                }
            } while(!result);

            Console.WriteLine("A =");
            Console.WriteLine(A);
            Console.WriteLine();

            Console.WriteLine("X =");
            Console.WriteLine(x);
            Console.WriteLine();

            Console.WriteLine("P =");
            Console.WriteLine(P);
            Console.WriteLine();

            Console.WriteLine("Q =");
            Console.WriteLine(Q);
            Console.WriteLine();

            Console.Read();
        }

        private static void q3()
        {
            string Nstr = "720062263747350425279564435525583738338084451473999841826653057981916355690188337790423408664187663938485175264994017897083524079135686877441155132015188279331812309091996246361896836573643119174094961348524639707885238799396839230364676670221627018353299443241192173812729276147530748597302192751375739387929";

            BigInteger N;
            BigInteger.TryParse(Nstr, out N);
            BigInteger sixN = 24 * N;
            BigInteger fourthRootofN = Sqrt(Sqrt(N));
            int numdigits = (int)BigInteger.Log10(fourthRootofN) + 5;

            BigInteger A = Sqrt(sixN);
            BigInteger threeP, twoQ, x;

            bool result = false;
            do
            {
                A++;
                fourthRootofN--;
                //Console.Write("\r" + fourthRootofN + new string(' ',numdigits - (int)BigInteger.Log10(fourthRootofN)));

                x = Sqrt(A * A - sixN);

                threeP = A - x;
                twoQ = A + x;

                if(threeP * twoQ == sixN)
                {
                    result = true;
                }
                else if (fourthRootofN < 0)
                {
                    Console.WriteLine("ERROR!");
                    result = true;
                }
            } while(!result);

            //Console.WriteLine("\r" + new string(' ',numdigits));
            Console.WriteLine("A =");
            Console.WriteLine(A);
            Console.WriteLine();

            Console.WriteLine("X =");
            Console.WriteLine(x);
            Console.WriteLine();

            Console.WriteLine("P =");
            Console.WriteLine(threeP / 6);
            Console.WriteLine();

            Console.WriteLine("Q =");
            Console.WriteLine(twoQ / 4);
            Console.WriteLine();

            Console.Read();
        }


        private static BigInteger Sqrt(BigInteger n)
        {
            if(n == 0) return 0;
            if(n > 0)
            {
                int bitLength = Convert.ToInt32(Math.Ceiling(BigInteger.Log(n, 2)));
                BigInteger root = BigInteger.One << (bitLength / 2);

                while(!isSqrt(n, root))
                {
                    root += n / root;
                    root /= 2;
                }

                return root;
            }

            throw new ArithmeticException("NaN");
        }

        private static Boolean isSqrt(BigInteger n, BigInteger root)
        {
            BigInteger lowerBound = root * root;
            BigInteger upperBound = (root + 1) * (root + 1);

            return (n >= lowerBound && n < upperBound);
        }
    }

}
