#include<iostream>

using namespace std;

void swap(int& a, int& b)
{
	int t=a;
	a=b;
	b=t;
}

void selSort(int* A, int left, int right)
{
	int ctr=left;
	for(ctr;ctr<=right;ctr++)
	{
		int min=ctr;
		for(int x=ctr;x<=right;x++)
		{
			if(A[min]>A[x])
				min=x;
		}
		swap(A[min], A[ctr]);
	}
}
int select(int* A, int left, int right)
{
	int n=right-left+1;
	int size=n/5+1;
	int* med=new int[size];
	int k=0;

	for(int ctr=left;ctr<=(right-(n%5));ctr+=5)
	{
		selSort(A, ctr, ctr+4);
		med[k++]=A[ctr+2];
	}

	for(int ctr=(n-(n%5));ctr<n;ctr++)
		{
			int min=ctr;
			for(int j=ctr;j<n;j++)
			{
				if(A[j]<A[min])
					min=j;
			}
			swap(A[ctr],A[min]);
		}

	if(n%5)		med[k++]=A[((n-1)+(n-(n%5)))/2];

	if(n<=5)
		return A[(n-1)/2];
	else
	{
		if(n%5)
			return select(med,0, k-1);
		else
			return select(med,0,k );
	}
}

int partition(int* A, int left, int right, int pivot)
{
	int i=left, j=right;
	while(i<j)
	{
		while(A[i]<A[pivot])
			i++;
		while(A[j]>=A[pivot])
			j--;
		if(i<j)
			swap(A[i],A[j]);
	}
	swap(A[pivot], A[i]);
	return i;
}

void Qsort(int* A, int left, int right)
{
	if(left<right)
	{
		int med=select(A,left,right);
		int pvt=med;
		for(int i=left;i<=right;i++)
		{
			if(A[i]==med)
				pvt=i;
		}

		int k=partition(A,left,right,pvt);
		Qsort(A,left,(k-1));
		Qsort(A,(k+1),right);
	}
}

/*void main()
{
	int test[10] ={11,21,3,4,15,6,7,8,9,10};

	Qsort(test,0,9);
	for(int i=0;i<=9;i++)
		cout<<test[i]<<' ';
}*/