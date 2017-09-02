#include<fstream>
#include<iostream>
using namespace std;

void main()
{
	ofstream fout("F:\\ASCII.txt");
	for(int i=0;i<=256;i++)
	{
		if(i==13)
			continue;
		//fout<<i<<' '<<(char)i<<endl;
		cout<<i<<' '<<(char)i<<endl;
	}
}