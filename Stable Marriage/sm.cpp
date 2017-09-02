#include <iostream>
#include <conio.h>
using namespace std;

int search(int* A,int n, int key)
{
	for(int i=0;i<n;i++)
		if(A[i]==key)
			return i;
	return -1;
}
int main()
{
//	int** male,** female;
	int male[3][3]={{1,2,0},{1,2,0},{1,2,0}};
	int female[3][3]={{2,1,0},{2,1,0},{2,1,0}};
	int* engaged;
	int n;
	cout<<"Enter the number of pairs:";
	cin>>n;
	engaged=new int[n];
	int* maleEngaged=new int[n];
	int* femaleEngaged=new int[n];
/*	male=new int*[n];
	female = new int*[n];
	for(int i=0;i<n;i++)
	{
		male[i]=new int[n];
		female[i]=new int[n];
	}
	for(int i=0;i<n;i++)
	{
		maleEngaged[i]=-1;
		cout<<"Enter the preference list of male "<<(i+1)<<" :\n";
		for(int j=0;j<n;j++)
		{
//			cout<<"Enter preference no."<<(j+1)<<": ";
			cin>>male[i][j];
			male[i][j]--;
		}
	}

	for(int i=0;i<n;i++)
	{
		femaleEngaged[i]=-1;
		cout<<"Enter the preference list of female "<<(i+1)<<" :\n";
		for(int j=0;j<n;j++)
		{
//			cout<<"Enter preference no."<<(j+1)<<": ";
			cin>>female[i][j];
			female[i][j]--;
		}
	}*/

	for(int i=0;i<n;i++)
	{
		maleEngaged[i]=-1;
		femaleEngaged[i]=-1;
	}
L:	for(int i=0;i<n;i++)				//male i
	{
		if(maleEngaged[i]>=0)
			continue;
		for(int j=0;j<n;j++)			//preference j
		{
			if((femaleEngaged[j]==-1))		//Female j is free
			{	maleEngaged[i]=j;
				femaleEngaged[j]=i;
				break;
			}
			else						//Female j is engaged
			{
				int k=search(female[j],n,i);
				if(k<femaleEngaged[j])		//(i,j is a better match) than present match
				{
					maleEngaged[femaleEngaged[j]]=-1;
					maleEngaged[i]=j;
					femaleEngaged[j]=i;
					break;
				}
			}
		}
	}
	int ready=1;
	for(int i=0;i<n;i++)
	{
		if(maleEngaged[i]==-1)
		{
			ready=0;
			goto L;
		}

	}
	if(ready)
	{
		for(int i=0;i<n;i++)
			cout<<endl<<"Male "<<(i+1)<<" is paired with female "<<(maleEngaged[i]+1);
	}
	_getch();
	return 0;
}