/*Modified algorithm of quicksort to:
1) Reduce the worst case complexity to O(n lg n)
2) Find the k-th smallest element in the list.
Author: Ujjwal Sen, 0900107
Date: Jan 18, 2011
*/
#include<iostream.h>

void swap(int& a, int& b)
{
	int t=a;
	a=b;
	b=t;
}
int Partition(int* A, int n, int pivot)
{
	int left=0,
	right=n-1;
  //	swap(A[right],A[pivot]);
	while(left<n && right>-1 && left<=right)
	{
		if(A[left]>A[pivot])
		{
			if(A[right]<A[pivot])
				swap(A[left], A[right]);
			else
				right--;
		}
		else
			left++;
	}
	swap(A[right], A[pivot]);
	return right;
}

int Select(int* A, int n)            	//Return index of the median
{
	if(n==1)
		return A[0];

	int* temp=new int[5];
	int size=n/5+1;
	int* med=new int[size];
	int k=0;

	for(int i=4;i<n;i+=5)
	{
		for(int j=0;j<5;j++)
			temp[j]=A[i-4+j];
													//Sorting temp
		for(int j1=0;j1<5;j1++)
		{
			int min=j1;
			for(int j2=j1;j2<5;j2++)
				if(temp[j2]<temp[min])
					min=j2;
			swap(temp[min],temp[j1]);		//temp Sorted
		}
		med[k++]=temp[2];
	}

	int np=n-i+4;								//Last group
	for(int t=0;t<np;t++)
		temp[t]=A[n-t-1];

	for(int j1=0;j1<5;j1++)
	{
		int min=j1;
		for(int j2=j1;j2<5;j2++)
			if(temp[j2]<temp[min])
				min=j2;
		swap(temp[min],temp[j1]);		//temp Sorted
	}

	med[n/5]=temp[2];
  return	Select(med,size);
}

int kthSmallest(int* A, int left, int right, int k)
{
	int n=right-left+1;

	int x=Select(A,n);
	int pivotFinal=Partition(A,n,x);

	if(pivotFinal==k)
		return A[pivotFinal];
	else if(pivotFinal>k)
		return kthSmallest(A,left, pivotFinal,k);
	else
		return kthSmallest(A,pivotFinal, right,k);
}

void QSortMod(int* A,int left, int right)
{
	int n=right-left+1;
	if(left>=right)
		return;
	int pivot=Select(A,n);
	int newIdx=Partition(A,n,pivot);
	QSortMod(A,left,newIdx-1);
	QSortMod(A,newIdx+1, right);
}

void main()
{
	int n,k;
	cout<<"Enter the number of elements in the array: ";
	cin>>n;
	int* A=new int[n];
	for(int i=0;i<n;i++)
	{
		cout<<"Enter element "<<(i+1)<<" of the array: ";
		cin>>A[i];
	}
	cout<<"Enter k: ";
	cin>>k;
	cout<<"The kth Smallest element is: "<<kthSmallest(A,0,n-1,k);
	cout<<"\n\nThe unsorted array is:\n";
	for(i=0;i<n;i++)
		cout<<A[i]<<' ';

//	QSortMod(A,0,n-1);

	cout<<"\n\nThe sorted array is:\n";
	for(i=0;i<n;i++)
		cout<<A[i]<<' ';
}
