//Author: Ujjwal Sen, 0900107
//Date: 4/11/2010

#include<fstream>
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;

struct set						//Stores the non terminals of the recognition matrix T[i][j]
{
	char a[5];
	int w[5];					//Number of times a[i] is inserted into the recognition matrix
	int n;

	set()	{n=0;}

	int lsearch(char key);

	void U(char c)	
	{
		int x=lsearch(c);		//Checks whether c is already present or not
		if(x==-1)				//If not present, insert c and initialise weight of c to 1
		{
			a[n++]=c;
			w[n-1]=1;
		}
		else					//If c is already present, increment weight
			w[x]++;
	}

};

int set::lsearch(char key)		//Linearly searches for key in the array
{
	for(int i=0;i<n;i++)
	{
		if(key==a[i])
			return i;			//If found, return the first occurence
	}
	return -1;					//Return -1 if not found
}


int lexsearch(char a[][3], char t, char NT, int n=11)
								//Searches for the lexical rule NT->t in the grammar
{
	for(int i=0;i<n;i++)
	{
		if(a[i][0]==NT && a[i][1]==t && a[i][2]=='*')
			return (i+1);		//Return the successor of the index where the rule was found
	}
	return 0;					//Return 0 if not found
}

set T[15][15];
char g[100][3];
void parse(int i, int j, char A, char* s);
ofstream fout, mat;
int npt=1;

void cky(char g[][3],unsigned int num, char s[],char goal)
{
	unsigned int i=0,j=0,k=0;
	unsigned int n=strlen(s)+1;

	for(i=0;i<n;i++)
	{
		for(j=0;j<num;j++)
		{
			if((g[j][1]==s[i])&&(g[j][2]=='*'))							//If there is a lexical rule A->s[i] in ithe grammar
			{
				T[i][i+1].U(g[j][0]);									//Insert the non terminal A in the recognition matrix at T[i][i+1]
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
				for(int m=0;m<T[i][k].n;m++)						//Select a non terminal T[i][k].a[m]( =B, say)
				{
					for(int z=0;z<num;z++)
					{
						if(g[z][1]==T[i][k].a[m])
						{
							if(T[k][j].lsearch(g[z][2])!=-1)		//If there exists a non terminal in T[k][j](=C, say)
																	//Such that there exists a non terminal A such that 
																	//A->BC is a production rule
							{
								T[i][j].U(g[z][0]);					//Insert A in T[i][j]
							}
						}
					}
				}
			}
		}
	}

	if(T[0][n-1].lsearch(goal)!=-1)									//If T[0][n-1] contains the goal symbol, the string is recognised
	{
		cout<<"Yes"<<endl;
		parse(0,n-1,goal,s);										//Construct parse tree if the string is valid
	}
	else
		cout<<"No"<<endl;
}

void parse(int i, int j, char A, char* s)
{
	int flag[15][15];													//Stores 0 if T[i][j] is not visited, 1 otherwise
																		//Used to detect ambiguities

	for(int x=0;x<15;x++)												//Initialise flag matrix
	{
		for(int y=0;y<15;y++)
			flag[x][y]=0;
	}

	int k=lexsearch(g,s[i],A);											//Searches for lexical rule A->s[i] in the grammar
	if(((j-i)==1) &&(k))
	{
		//fout<<k<<' ';
		fout<<g[k-1][0]<<'='<<g[k-1][1]<<',';
		return;
	}

	for(int k1=(i+1);k1<j;k1++)											//k1 iterates from i to j; i.e i<k1<j
	{
		for(int z1=0;z1<T[i][k1].n;z1++)								//Selects B from T[i][k1]
		{
			for(int z2=0;z2<T[k1][j].n;z2++)							//Selects C from T[k1][j]
			{
				for(int y1=0;y1<11;y1++)
				{
					if((A==g[y1][0]) && (T[i][k1].a[z1]==g[y1][1])&&(T[k1][j].a[z2]==g[y1][2]))
																	//If there exists a rule A->BC in the grammar
					{	
						if(!flag[i][j])
						{
							flag[i][j]=1;	
							if(A=='S'||y1==0||y1==1)
								fout<<endl;
							//fout<<(y1+1)<<' ';
							fout<<A<<"->"<<g[y1][1]<<g[y1][2]<<',';
							parse(i,k1,T[i][k1].a[z1],s);
							parse(k1,j,T[k1][j].a[z2],s);
						}
						else
						{
							if(A=='S'||y1==0||y1==1)	
								fout<<endl;
							//fout<<" or\n\t"<<(y1+1)<<' ';
							fout<<" or\n\t"<<A<<"->"<<g[y1][1]<<g[y1][2]<<',';
							npt++;
							parse(i,k1,T[i][k1].a[z1],s);
							parse(k1,j,T[k1][j].a[z2],s);
						}
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
	fout.open("f:\\temp\\cky.txt");
	ofstream op("f:\\temp\\output.txt",ios::app);
	//op<<"NS\tNPT\tString\n";
	 fout<<( "The line entered was: %s\n", line );
	int n=11;

	char goal;
	cout<<"Specify goal symbol:";
	cin>>goal;

	g[0][0]='S';	g[0][1]='A';	g[0][2]='B';			//Given Grammar
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

	mat.open("f:\\temp\\matrix.txt");
	cky(g,n,line,goal);
	fout.close();
	int q=strlen(line);

	for(int i=0;i<=q;i++)
		mat<<'\t'<<i;
	for(int i=0;i<=q;i++)
	{
		mat<<'\n'<<i<<": ";
		for(int j=0;j<=q;j++)
		{	
			mat<<'\t';
			for(int z=0;z<T[i][j].n;z++)
				mat<<T[i][j].a[z]<<'('<<T[i][j].w[z]<<"),";
		}
	}
	mat.close();
	int idx=T[0][q].lsearch('S');
	op<<T[0][q].w[idx]<<'\t'<<npt<<'\t'<<line<<'\n';
}