#include "RB.h"
void main()
{
	RedBlack T;
	int n;
	cout<<"Enter the number of elements you want to insert:";
	cin>>n;
	for(int i=1;i<=n;i++)
		T.insert(i);
	cout<<T.blackHeight(T.retRoot())<<"\n\n\n";
	T.display();
}
