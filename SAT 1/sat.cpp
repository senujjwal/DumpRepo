#include"set.h"
#include<process.h>
#include<string.h>
#include<math.h>
#include<fstream>
void store(set **a,int n,int p,int q,int r)
{
	int p1,q1;
	if(p<0)
		p1=-p-1;
	else
		p1=n-p;

	if(q<0)
		q1=-q-1;
	else
		q1=n-q;

	if(r>0)
		a[p1][q1].U(r);
	else
		a[p1][q1].U(r);
	a[p1][q1].U(p);
	a[p1][q1].U(q);
}

int limit(char* s)
{
	ifstream fin(s);
	int a;
	fin>>a;
	int max=a;
	int min=a;
	while(!fin.eof())
	{
		if(a>max)
			max=a;
		if(a<min)
			min=a;
		fin>>a;
	}
	max=abs(max);
	min=abs(min);
	fin.close();
	return (max>min)?max:min;
}
int warp(int x, int n)
{
	if(x<0)
		return n-x;
	else
		return x-1;
}



set B, **W;
int sFlag;
int lim;
int **F;

void wClosure(set A)
{
	set R;
	B.clear();			//Restores B to NULL
	sFlag=1;
	int bUpdt=0;
	//R.clear();
	R.U(A,B);
	while(!bUpdt)
	{
		int iSize=R.retsize();
		int rUpdt=1;
		while(rUpdt)
		{
			if(!R.chkLit())
			{
				sFlag=0;
				return;
			}
			else
			{
				node* m=R.retHead();
				int m1=warp(m->info,R.retsize());
				while(m!=NULL)
				{
					node* l=R.retHead();
					int l1=warp(l->info,R.retsize());					
					while(l!=NULL)
					{	
						B.U(B,W[m1][l1]);
						R.U(R,B);
						l=l->next;
					}
					m=m->next;
				}
				int fSize=R.retsize();
				if(iSize==fSize)
					rUpdt=0;
			}
		}													//2.2.3
		set C;

		for(int i=1;i<=lim/2;i++)
		{
			C.U(i);
			if(R.lsearch(i)!=NULL||R.lsearch(-i)!=NULL)
				continue;
		}

		for(int i=1;i<=lim/2;i++)
		{
			C.U(-i);
			if(R.lsearch(i)!=NULL||R.lsearch(-i)!=NULL)
				continue;
		}

		int c=C.retsize();
		set* L;
		L=new set[C.retsize()];

		node* p=C.retHead();
		while(p!=0)
		{
			int ci=warp(p->info,c);

			L[ci].U(p->info);

			node* r1=R.retHead();
			while(r1!=0)
			{
				int x1=warp(r1->info,R.retsize());

				node* q=W[x1][ci].retHead();
				while(q!=0)
				{
					if(C.lsearch(q->info)!=0)
						L[ci].U(q->info);
					q=q->next;				
				}
				r1=r1->next;
			}
			p=p->next;
		}												//2.3

		int* liUpd=new int[c], liUpdt=1;
		for(int i=0;i<c;i++)
			liUpd[i]=0;

		while(liUpdt && !bUpdt)
		{
			for(int i=0;i<c;i++)
			{
				int iSize=L[i].retsize();

				node* li=L[i].retHead();
				while(li!=0)
				{
					int ln=warp(-(li->info),L[i].retsize());
					L[ln].U(-i);
					li=li->next;
				}

				li=L[i].retHead();
				while(li!=0)
				{
					set temp;
					temp.U(R,L[i]);
					int ts=temp.retsize();
					node* t=temp.retHead();
					while(t!=0)
					{
						int m=warp(t->info,ts);

						node* t1=temp.retHead();
						while(t1!=0)
						{
							int l=warp(t1->info,ts);

							node* wml=W[m][l].retHead();
							while(wml!=0)
							{
								if(C.lsearch(wml->info)!=0)
									L[i].U(wml->info);
								wml=wml->next;
							}

							t1=t1->next;
						}
						t=t->next;
					}
					li=li->next;
				}

				int fSize=L[i].retsize();
				if(iSize==fSize)
				{
					liUpd[i]=0;
				}

				liUpdt=0;
				for(int j=0;j<c;j++)
				{
					if(liUpd[j])
						liUpdt++;
				}										//2.4.4
			}

			for(int i=0;i<c;i++)
			{
				if(!L[i].chkLit())
					B.U(-i);
			}
		}
	}													//2.5
}

void sat(set L)
{	
	set T;
	int lit=L.retsize();
	int change=0;
	do
	{
		//0
		node* x=L.retHead();
		while(x!=NULL)
		{
			int x1=warp(x->info,L.retsize());
			node* y=L.retHead();
			while(y!=NULL)
			{
				int y1=warp(y->info,L.retsize());
				int yn1=warp(-y->info,L.retsize());

				if(y==x)
					y=y->next;

				set temp;
				int iSize=W[x1][y1].retsize();

				temp.INT(W[x1][y1],W[x1][yn1]);
				W[x1][x1].U(W[x1][x1],temp);
				temp.clear();

				int fSize=W[x1][y1].retsize();

				if(iSize!=fSize)
					change=1;
				y=y->next;
			}
			x=x->next;
		}													//0.a.4

		x=L.retHead();										
		while(x!=NULL)										//0.b
		{
			int x1=warp(x->info,L.retsize());

			node* y=L.retHead();

			set* Ly=new set[L.retsize()-1];
			while(y!=NULL)
			{
				int y1=warp(y->info,L.retsize());

				if(y==x)
					y=y->next;
				//			int y1=warp(y->info,L.retsize());
				set temp1;

				temp1.U(W[x1][x1],W[y1][y1]);

				node* t1=temp1.retHead();
				while(t1!=0)
				{
					if(W[x1][y1].lsearch(t1->info)!=0)
						Ly[y1].U(t1->info);
					t1=t1->next;
				}
				y=y->next;
			}

			y=L.retHead();									//0.b.3
			while(y!=0)
			{
				int y1=warp(y->info,lit);
				int lys=Ly[y1].retsize();

				node* ly=Ly[y1].retHead();
				while(ly!=0)
				{
					int ln=warp(ly->info,lys);
					if(!(Ly[ln].lsearch(-(y->info))))
					{
						Ly[ln].U(-(y->info));
						change=1;
					}
				}
				y=y->next;
			}
			x=x->next;
		}

		x=L.retHead();
		while(x!=0)
		{
			int x1=warp(x->info,lit);
			node* y=L.retHead();
			while(y!=0 && ((x->info)>(y->info)))
			{
				int y1=warp(y->info,lit);
				node* w2=W[y1][x1].retHead();
				while(w2!=0)
				{
					if(!W[x1][y1].lsearch(w2->info))
					{			
						W[x1][y1].U(W[x1][y1],W[y1][x1]);
						W[y1][x1].U(W[x1][y1],W[y1][x1]);
						change=1;
					}
					y=y->next;
				}
			}
			x=x->next;
		}
		//1

		x=L.retHead();
		while(x!=0)
		{
			if(T.lsearch(x->info))							//x not in T
				x=x->next;
			int x1=warp(x->info,lit-T.retsize());
			node* y=L.retHead();
			while(y!=0)
			{			
				if(T.lsearch(y->info))						//y not in T
					y=y->next;
				int y1=warp(y->info,lit-T.retsize());

				set t1;
				t1.U(W[x1][y1],W[x1][x1]);
				t1.U(T,W[y1][y1]);							//1.1

				wClosure(W[x1][y1]);						//1.2

				W[x1][y1].U(W[x1][y1],B);					//1.3

				if(!sFlag)
				{
					F[x1][y1]=0;
					if(!W[x1][x1].lsearch(-(y->info)))
					{
						W[x1][x1].U(-y->info);
						change=1;
					}
					if(!W[y1][y1].lsearch(-(x->info)))
					{
						W[y1][y1].U(-x->info);
						change=1;
					}
				}
				y=y->next;
			}
			x=x->next;
		}

		//2
		x=L.retHead();
		while(x!=0)
		{
			int x1=warp(x->info,lit);
			if(!(T.lsearch(-(x->info))) && !(W[x1][x1].chkLit()))
			{
				F[x1][x1]=0;
				T.U(-(x->info));
				wClosure(T);
				if(!sFlag)
				{
					cout<<"The given formula is unsatisfiable.";
					return;
				}
				change=1;
			}
			x=x->next;
		}

		//3
		x=L.retHead();
		while(x!=0)
		{
			int x1=warp(x->info,lit);
			node* a=W[x1][x1].retHead();
			while(a!=0)
			{
				int an=warp(-(a->info),W[x1][x1].retsize());
				if(!W[an][an].lsearch(-(x->info)))
				{
					W[an][an].U(-(x->info));
					wClosure(W[an][an]);
					W[an][an].U(W[an][an],B);
					if(!sFlag)
					{
						F[an][an]=0;
						T.U(a->info);
						wClosure(T);
						T.U(T,B);
						if(!sFlag)
						{
							cout<<"The given formula is unsatisfiable.";
							return;
						}
						change=1;					
					}
				}
				a=a->next;
			}
			x=x->next;
		}
		//4
		x=L.retHead();
		while(x!=0)
		{
			int x1=warp(x->info,lit);
			node* a=W[x1][x1].retHead();
			int a1=warp(a->info,W[x1][x1].retsize());
			int iSize=W[x1][x1].retsize();
			W[x1][x1].U(W[x1][x1],W[a1][a1]);
			int fSize=W[x1][x1].retsize();

			x=x->next;
		}
	}while(!change);						//IV over
}

void main()
{
	char s[100];
	cout<<"Enter path of data set: ";
	gets_s(s,100);

	ifstream fin(s);
	int x1,x2,x3;
	int i=0,clause=0;
	set L;

	fin>>x1;

	fin.close();
	lim=2*limit(s);
	fin.open(s);

	W=new set*[lim];
	for(int i=0;i<lim;i++)
		W[i]=new set[lim];
	i=0;
	while(i<=clause&&!fin.eof())
	{
		fin>>x2;
		fin>>x3;
		if(x2==0&&x3==0)
		{
			clause=x1;
			fin>>x1;
			fin>>x2;
			fin>>x3;
		}

		store(W,lim,x1,x3,x2);
		store(W,lim,x1,x2,x3);
		store(W,lim,x2,x1,x3);
		store(W,lim,x2,x3,x1);
		store(W,lim,x3,x1,x2);
		store(W,lim,x3,x2,x1);
		fin>>x1;
		i++;
	}
	for(int i=1;i<=lim/2;i++)
		L.U(i);
	for(int i=1;i<=lim/2;i++)
		L.U(-i);

	sat(L);
	for(int i=0;i<lim;i++)
		delete W[i];

	fin.close();
}