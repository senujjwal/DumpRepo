#include<fstream>
#include<iostream>
using namespace std;

struct node
{
	int key[9];				//Array to store key values in the node
	int n;						//Number of keys filled in a node
	node* ptr[10];				//Array to store pointers to children
	node* parent;				//Pointer to the parent node(NULL for the root). Only a facility, not used in the algorithm
	bool isleaf;				//Boolean value to store whether a node is a leaf or not

/*	node()
	{
		n=0;
		isleaf=true;
	}*/
};

ofstream fout("F:\\temp\\Btree.txt");

class Btree
{
private:
	node* root;
	void Split(node* x, int i);
	void insRec(node* x, int k);
public:
	Btree();
	~Btree();

	node* retRoot()	{return root;}
	void setRoot(node* p)	{root=p;}

	void insert(int k);
	void clear(node*);
	node* search(node* p,int x);
	void display(node*);
};

void Btree::Split(node* x, int idx)			//x is non full, x->ptr[idx] is full and is causing the split
{
	node* z=new node;
	node* y=x->ptr[idx];

	y->n=4;
	z->isleaf=y->isleaf;
	z->n=4;
	z->parent=x;
	for(int i=0;i<4;i++)
	{
		z->key[i]=y->key[i+5];
		z->ptr[i]=y->ptr[i+5];
	}
	for(int i=x->n;i>idx;i--)
		x[i]=x[i-1];

	x->key[idx]=y->key[4];
	x->ptr[idx]=y;
	x->ptr[idx+1]=z;
	(x->n)++;
}

void Btree::insRec(node *x, int k)
{
	int i=(x->n);
	if(x->isleaf)
	{
		for(i=(x->n);i>=0 && k<x->key[i];i--)
			x->key[i]=x->key[i-1];
		x->key[i]=k;
		(x->n)++;
	}

	else
	{
		for(i=(x->n);i>=0 && k<x->key[i];i--);
		
		if(x->ptr[i]->n==9)
		{
			Split(x,i);
			if(k>x->key[i])
				i++;
		}
		insRec(x->ptr[i],k);
	}
}

Btree::Btree()
{
	root=new node;
	root->isleaf=1;
	root->n=0;
	root->parent=NULL;
	for(int i=0;i<9;i++)
	{
		root->ptr[i]=NULL;
		root->key[i]=0;
	}
	root->ptr[9]=NULL;

}


Btree::~Btree()
{
	clear(root);
}


void Btree::insert(int k)
{
	node* r=root;
	if(r->n==9)
	{
		node* s=new node;
		s->isleaf=false;
		s->n=0;
		s->ptr[0]=r;
		root=s;
		r->parent=s;
		Split(s,0);
		insRec(s,k);
	}
	else
		insRec(r,k);
}


void Btree::clear(node* p)
{
	if(p->isleaf)
	{
		delete p;
		return;
	}
	for(int i=0;i<=(p->n);i++)
	{
		if(p->ptr[i]!=NULL)
			clear(p->ptr[i]);
	}
	delete p;
}

node* Btree::search(node* p, int x)
{
	node *ret=NULL;
	for(int i=0;i<=9;i++)
	{
		if(i==9)
			ret= search(p->ptr[9],x);
		else if(p->key[i]==x && ret==NULL)
			ret= p;
		else if(p->key[i]>x && ret==NULL)
			ret=search(p->ptr[i],x);
	}
	return ret;
}


void Btree::display(node* r)
{
	if(r->isleaf)
	{
		for(int i=0;i<(r->n);i++)
			fout<<r->key[i]<<' ';
		fout<<'\t';
		return;
	}
	for(int i=0;i<(r->n)+1;i++)
		display(r->ptr[i]);
	fout<<'\n';
	for(int i=0;i<(r->n);i++)
		fout<<r->key[i]<<' ';
}