# include "B tree.h"

void main()
{
	Btree BT;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
		BT.insert(i);
	BT.display(BT.retRoot());
	cout<<endl;
}