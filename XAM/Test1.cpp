#include<iostream>
using namespace std;

typedef unsigned int ui;
class string
{
	char* a;
	ui size;
	int* prefix(string T);
public:
	string()	{a=NULL; size=0;}
	string(int n)	{a=new char[n]; size=n;}
	void insert(char* s)
	{
		for(int i=0;i<size && s[i]='/0';i++)
			a[i]=s[i];
	}
	int KMP1(string T, string P);						//Match pattern P in text T	
};

