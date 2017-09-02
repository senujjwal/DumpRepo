using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ListFiles
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("This is a dir simulator program.");
            System.IO.DirectoryInfo dir = new System.IO.DirectoryInfo(@"C:\");

    foreach (System.IO.FileInfo file in dir.GetFiles("*.*"))
    {
        Console.WriteLine("{0}, {1}", file.Name, file.Length);
    }
//    Console.ReadLine();

        }
    }
}
