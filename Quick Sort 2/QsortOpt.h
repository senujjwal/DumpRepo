#include<iostream>
typedef unsigned int ui;
void swap(int& a, int& b)
{
	int t=a;
	a=b;
	b=t;
}

class myArray
{
	int* A;
	int n;
public:
	myArray()
	{
		A=0;
		n=0;
	}
	myArray(int n)
	{
		this->n=n;
		A=new int[n];
	}
	~myArray()
	{
		delete A;
	}
	void Qsort(int left, int right);
	inline void Qsort()	{Qsort(0,n-1);}
	void SelSortMod(int left, int right);
	inline ui Min(int left,int right);
	inline ui Min()	{Min(0,n-1);}
	int Partition(int pivot);
	int Select();
};

ui myArray::Min(int left,int right)
{
	int min=left;
	for(int i=left;i<right;i++)
	{
		if(A[i]<A[min])
			min=i;
	}
	return min;
}
void myArray::SelSortMod(int left, int right)
{
	for(int i=left;i<=right;i++)
	{
		ui min=Min(i,right);
		swap(A[i],A[min]);
	}
}
int myArray::Partition(int pivot)
{
	int left=0,
	right=n-1;
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

void myArray::Qsort(int left, int right)
{
	right=(this->n)-1;
	if(left>=right)
		return;
	int pivot=Select();
	int newIdx=Partition(pivot);
	Qsort(left,newIdx-1);
	Qsort(newIdx+1, right);

}