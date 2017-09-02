#include<iostream>
using namespace std;
//#include<conio.h>

struct node
{
	int info;
	node* next;
};

class set
{
	node* head;
	int size;

public:
	set();
	set(int n);

	void display();
	node* retHead()	{return head;}
	int retsize()	{return size;}
	node* lsearch(int key);
	int chkLit();

	void insertBeg(int n);
	void insertLast(int n);
	void U(int n){insertBeg(n);}

	void U(set A,set B);
	void delBeg();
	void delLast();
	void delnode(int n);
	void clear();
	void INT(set A, set B);
};

void set::INT(set A, set B)
{
	node* a=A.retHead();
	while(a!=NULL)
	{
		if(B.lsearch(a->info)!=NULL)
			U(a->info);
		a=a->next;
	}
}
void set::U(set A,set B)
{
	node* a=A.retHead();
	node* b=B.retHead();
	while(a!=NULL)
	{
		U(a->info);
		a=a->next;
	}
	while(b!=NULL)
	{
		U(b->info);
		b=b->next;
	}
}
void set::clear()
{
	while(size)
	{
		delBeg();
		size--;
	}
}
set::set()
{
	head=NULL;
	size=0;
}

set::set(int n)
{
	head=new node;
	head->info=n;
	head->next=NULL;
	size=0;
}

void set::display()
{
	node* p=head;
	while(p!=NULL)
	{
		cout<<p->info<<' ';
		p=p->next;
	}
}

int set::chkLit()
{
	node* p=head;
	while(p!=NULL)
	{
		if(lsearch(-p->info)!=NULL)
			return 0;
		p=p->next;
	}
	return 1;
}

node* set::lsearch(int key)
{
	node* p=head;
	while(p->next!=NULL)
	{
		if(p->info==key)
			return p;
		p=p->next;
	}
	return NULL;
}

void set::insertBeg(int n)
{
	node* p=new node;
	p->info=n;
	p->next=NULL;

	if(head==NULL)
		head=p;

	else
	{
		p->next=head->next;
		head->next=p;
	}
	size++;
}

void set::insertLast(int n)
{
	node* p=new node;
	p->info=n;
	p->next=NULL;

	if(head==NULL)
		head=p;

	else
	{
		node* save=head;
		node* t=head;
		while(t!=NULL)
		{
			save=t;
			t=t->next;
		}
		save->next=p;
	}
	size++;
	delete p;
}

void set::delBeg()
{
	node* save=head->next;
	head->next=save->next;
	cout<<"Deleting element with info "<<save->info;
	delete save;
	size--;
}

void set::delLast()
{
	node* save=head;
	node* p=head;
	while(p!=NULL)
	{
		save=p;
		p=p->next;
	}
	cout<<"Deleting element with info "<<save->info;
	delete save;
	size--;
}

void set::delnode(int key)
{
	node* save=head->next;
	node* p=head;
	while(save!=NULL)
	{
		save=p->next;
		if(save->info==key)
		{
			p->next=save->next;
			cout<<"\nDeleting node with info "<<save->info;
			size--;
			delete save;
		}
		p=p->next;
	}
	cout<<"Node not found";
}

