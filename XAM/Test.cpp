# include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

int* fail(char* P,int m)
{
	int* f=new int[m];
	int i=0,j=0;
	while(i<m)
	{
		if(P[i]==P[j])			//Matched j+1 characters
			f[i++]=++j;

		else if(j>0)
			j=f[j-1];

		else
			f[i++]=0;
	}
	return f;
}

int KMP(char* T, char* P)
{
	int i=0,j=0;
	int m=strlen(P);
	int* f=fail(P,m);
	int n=strlen(T);
	while(i<n)
	{
		if(T[i]==P[j])
		{
			if(j==m-1)
				return 1;
			else
			{
				i++;
				j++;
			}
		}

		else
		{
			if(j>0)
				j=f[j-1];
			else
				i++;
		}
	}
	return 0;
}

void main()
{
	char T[100], P[10];
	cout<<"Enter text:";
	gets_s(T,99);
	cout<<"Enter pattern: ";
	gets_s(P,9);
	if(KMP(T,P))
		cout<<"true";
	else
		cout<<"False";
}