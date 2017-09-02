#include<fstream>
#include<string.h>

using namespace std;


class PQ
{
	int* A;
	int size, f,r;
public:
	PQ()	{A=0;size=f=r=0;}
	PQ(int n)
	{
		size=n;
		A=new int[n];
		f=r=-1;
	}

	void ins(int k);
	void del(int k);
};

void PQ::ins(int k)
{
	if(r==size-1)
		return;
	if(f>r)
	{
		f=r=0;
		A[r]=k;
	}
	else
	{
		int i;
		for(i=r;i>k;i--)
			A[i+1]=A[i];
		A[i]=k;
		r++;
	}
}

void PQ::del(int k)
{
	if(f==-1||f>r)
		return;
	if(f==r)
		f=r=-1;
	else
		f++;
}

class graph
{
	int** adj;
	int numV;

public:
	graph()	
	{	adj=0;
		numV=0;
	}

	graph(int n)
	{
		numV=n;
		adj=new int* [n];
		for(int i=0;i<n;i++)
			adj[i]=new int[n];

		for(int i=0;i<numV;i++)
		{
			for(int j=0;j<=i;j++)
				adj[i][j]=adj[j][i]=0;
		}
	}

	void createGraph();
	void addEdge(int i,int j,int wt)
	{
		if(i>=numV||j>=numV)
			return;
		adj[i][j]=adj[j][i]=wt;
	}

	graph kruskal();
	graph prim();
	void display();
	~graph()
	{
		for(int i=0;i<numV;i++)
			delete adj[i];
		delete adj;
	}
};

void graph::createGraph()
{
	char filePath[100]="F:\\kruskal.txt";
/*	cout<<"Enter the path of the input file: ";
	gets_s(filePath);*/
	ifstream fin(filePath);
	fin>>numV;

	adj= new int*[numV];
	for(int i=0;i<numV;i++)
		adj[i]=new int[numV];

	for(int i=0;i<numV;i++)
	{
		for(int j=0;j<=i;j++)
			adj[i][j]=adj[j][i]=0;
	}

	while(!fin.eof())
	{
		int a,b;
		fin>>b>>a;
		fin>>adj[a-1][b-1];
		adj[b-1][a-1]=adj[a-1][b-1];
	}
}

graph graph::kruskal()
{
	graph MST;
	return MST;
	//if
}

graph graph::prim()
{
	int * idx=new int[numV];
	idx[0]=0;
	int size=1;
	graph MST(numV);
	{
		graph empty;
		if(!numV)
			return empty;
	}


	return MST;
}

void graph::display()
{
	for(int i=0;i<numV;i++)
	{
		cout<<endl;
		for(int j=0;j<numV;j++)
			cout<<adj[i][j]<<' ';
	}
}

