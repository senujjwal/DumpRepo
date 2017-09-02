/*//Author: Ujjwal Sen, 0900107
//Date: 22/10/2010

#include<fstream>
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

struct set
{
	char a[30];
	int n;

	set()	{n=0;}

	int lsearch(char key);

	void U(char c)	{a[n++]=c;}

};

int set::lsearch(char key)
{
	for(int i=0;i<n;i++)
	{if(key==a[i])
	{return i;}}
	return -1;
}


int lsearch(char a[][3], char t, char NT, int n=11)
{
	for(int i=0;i<n;i++)
	{
		if(a[i][1]==t && a[i][0]==NT && a[i][2]=='*')
			return (i+1);
	}
	return 0;
}
set T[15][15];
char g[100][3];
void parse(int i, int j, char A, char* s);
ofstream fout;

void cky(char g[][3],int num, char s[],char goal)
{
	unsigned int i=0,j=0,k=0;
	unsigned int n=strlen(s)+1;

	for(i=0;i<n;i++)
	{
		for(j=0;j<num;j++)
		{
			if((g[j][1]==s[i])&&(g[j][2]=='*'))
			{
				T[i][i+1].U(g[j][0]);
			}
		}
	}

	for(int d=2;d<=n;d++)
	{
		for(i=0;i<=(n-d);i++)
		{
			j=d+i;
			for(k=(i+1);k<=(j-1);k++)
			{
				for(int m=0;m<T[i][k].n;m++)
				{
					for(int z=0;z<num;z++)
					{
						if(g[z][1]==T[i][k].a[m])
						{
							if(T[k][j].lsearch(g[z][2])!=-1)
							{
								T[i][j].U(g[z][0]);
							}
						}
					}
				}
			}
		}
	}

	if(T[0][n-1].lsearch(goal)!=-1)
	{
		cout<<"Yes"<<endl;
		parse(0,n-1,goal,s);
	}
	else
		cout<<"No"<<endl;
}

void parse(int i, int j, char A, char* s)
{
	int k=lsearch(g,s[i],A);
	if(((j-i)==1) &&(k))
	{
		fout<<g[k-1][0]<<'='<<g[k-1][1]<<endl;
		return;
	}

	for(int k1=(i+1);k1<j;k1++)
	{
		for(int z1=0;z1<T[i][k1].n;z1++)
		{
			for(int z2=0;z2<T[k1][j].n;z2++)
			{
				for(int y1=0;y1<11;y1++)
				{
					if((A==g[y1][0]) && (T[i][k1].a[z1]==g[y1][1])&&(T[k1][j].a[z2]==g[y1][2]))
					{
						fout<<A<<"->"<<g[y1][1]<<g[y1][2]<<endl;
						parse(i,k1,T[i][k1].a[z1],s);
						parse(k1,j,T[k1][j].a[z2],s);
					}
				}
			}
		}
	}
}

void main()
{
	cout<<"\nEnter the string to be parsed: ";
	char line[21]; // room for 20 chars + '\0'
	gets_s( line, 20 );
	 printf( "The line entered was: %s\n", line );
	int n=11;

	char goal;
	cout<<"Specify goal symbol:";
	cin>>goal;

	g[0][0]='S';	g[0][1]='A';	g[0][2]='B';
	g[1][0]='S';	g[1][1]='B';	g[1][2]='B';
	g[2][0]='A';	g[2][1]='A';	g[2][2]='B';
	g[3][0]='A';	g[3][1]='C';	g[3][2]='C';
	g[4][0]='A';	g[4][1]='a';	g[4][2]='*';
	g[5][0]='B';	g[5][1]='B';	g[5][2]='B';
	g[6][0]='B';	g[6][1]='C';	g[6][2]='A';
	g[7][0]='B';	g[7][1]='b';	g[7][2]='*';
	g[8][0]='C';	g[8][1]='B';	g[8][2]='A';
	g[9][0]='C';	g[9][1]='A';	g[9][2]='A';
	g[10][0]='C';	g[10][1]='b';	g[10][2]='*';
	fout.open("f:\\temp\\cky.txt");
	cky(g,n,line,goal);
	cout<<endl;
	fout.close();
}

*/