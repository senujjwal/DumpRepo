#include<iostream>
using namespace std;

void main()
{
	int i=0,n=20;
	for(int k=1;k<=n;k++)
	{
		double product = 1;
		for(i=2; i<=k; i++)
			product *= (double)(53 - i)/52;
	product = 1- product;
	cout <<"n is "<<k << "\tProduct is: "<<product<<endl;
	}
}