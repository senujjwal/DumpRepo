/*#include<iostream>
using namespace std;

void swap(int &a,int &b)
{
	int t=a;
	a=b;
	b=t;
}

int Partition(int* a, int left, int right)
{
	int x=a[right];
	int i=left-1;
	for(int j=left;j<right;j++)
	{
		if(a[j]<=x)
		{
			swap(a[++i],a[j]);
		}
	}
	swap(a[++i],a[right]);
	return i;
}

int PL1(int* a, int left, int right)
{
	int y=(left+right)/2;
	int x=a[y];
	int i=left,j=right;
	
	while(i<j)
	{
		while(a[i]<x && i<right)	i++;
		while(a[j]>x && j>left)		j--;
		if(i!=j)
			swap(a[i],a[j]);
	}
	if(j!=left)
		swap(x,a[j]);
	return i;
}

int PL(int* a, int left, int right)
{
	int y=left;
	int x=a[y];
	int i=left,j=right;
	while(i<j)
	{	
		while(a[i]<=x && i<right)	i++;
		while(a[j]>=x && j>left)	j--;
		swap(a[i],a[j]);
	}swap(x,a[j]);
	return i;
}

void Qsort(int* a, int left, int right)
{
	if(left>=right)
		return;

//	int k=Partition(a,left,right);
	int k=PL(a,left,right);
	Qsort(a,left,k-1);
	Qsort(a,k+1,right);
}

int main()
{
	int *a;
	int n;

	cout<<"Enter size of a: ";
	cin>>n;

	a=new int[n];
	int i;
	for(i=0;i<n;i++)
		//a[i]=n-i;
		cin>>a[i];

	//for(i=0;i<n;i++)	cout<<a[i]<<endl;
	
	Qsort(a,0,n-1);
	cout<<"\nThe sorted array is:\n";
	for(i=0;i<n;i++)	cout<<a[i]<<endl; 

	delete a;
	cout<<endl;
	return 0;
}*/