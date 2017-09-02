#include<iostream>
#include<math.h>
#define red 1
#define black 0
using namespace std;

struct node
{
	int key;
	bool color;			//RED or BLACK
	node* left;
	node* right;
	node* parent;
};

class RedBlack
{
	node* root;
	node* NIL;
	int bh;
	unsigned int size;
	
	void leftRotate(node* x);
	void rightRotate(node* x);
	void insfix(node*,node*);
	void delfix(node*);
	void Transplant(node* u, node* v);
public:
	void del(node*);
	RedBlack()	
	{
		NIL=new node;
		NIL->parent=NULL;
		NIL->color=false;
		root=new node;
		root=NIL;
		bh=0;
		size=0;
	}
	void clear(node* z)
	{
		if(z!=NIL)
		{
			clear (z->left);
			clear(z->right);
			delete z;
		}
		size--;
	}
	~RedBlack()
	{
		clear(root);
	}
	node* retRoot()	{return root;}
	int blackHeight(node* z);

	node** spine(node* z);
	void insert (int k);
	node* search(int k);
	node* succ(node*);
	node* pred(node*);
	node* TreeMin(node *z);
	void inorder(node *z);
	void preorder(node *z);
	void postorder(node *z);
	void display()	{inorder(root);}
};

int RedBlack:: blackHeight(node* z)
{
	if(z!=NIL)
	{
		if(z->color==black)
			bh=blackHeight(z->left)+1;
		else
			bh=blackHeight(z->left);
	}
	return bh;
}
void RedBlack::leftRotate(node* x)
{
	node* y=x->right;
	x->right=y->left;
	if(y->left!=NIL && y!=NIL)
		(y->left)->parent=x;

	y->parent=x->parent;

	if(y->parent==NIL)
	{root=y;}
	else if(x==(x->parent)->left)
	{(x->parent)->left=y;}
	else
	{(x->parent)->right=y;}
	y->left=x;
	x->parent=y;
}

void RedBlack::rightRotate(node* x)
{
	node* y=x->left;
	x->left=y->right;
	if(y->right!=NIL)
		(y->right)->parent=x;

	y->parent=x->parent;

	if(y->parent==NIL)						//If the tree is empty
	{root=y;}

	else if(x==(x->parent)->right)
	{(x->parent)->right=y;}
	else
	{(x->parent)->left=y;}
	y->right=x;
	x->parent=y;
}
void RedBlack::insert(int k)
{
	node* z=new node;
	z->color=true;
	z->key=k;
	z->left=z->right=z->parent=NIL;

	node* y=NIL;
	node* x=root;

	while(x!=NIL)
	{
		y=x;
		if(k<x->key)
			x=x->left;
		else
			x=x->right;
	}
	z->parent=y;	
	if(y==NIL)					//Tree is empty
		root=z;
	else if(k<(y->key))
		y->left=z;
	else
		y->right=z;
	insfix(root,z);
	size++;
}
void RedBlack::insfix(node* r, node* z)
{
	node* y;
	while(z->parent->color)
	{
		if((z->parent)==(((z->parent)->parent)->left))
		{
			y=z->parent->parent->right;								//y is z's "uncle"

			if(y->color)
			{
				z->parent->color=false;								//Make z's parent and uncle black and 
				y->color=false;
				z->parent->parent->color=1;
				z=z->parent->parent;								//z moves up 2 levels
			}

			else if(z==z->parent->right)							//z is a right child
			{
				z=z->parent;
				leftRotate(z);
			}

			z->parent->color=false;
			z->parent->parent->color=true;
			rightRotate(z->parent->parent);


		}
		else
		{
			y=z->parent->parent->left;								//y is z's "uncle"

			if(y->color)
			{
				z->parent->color=false;								//Make z's parent and uncle black
				y->color=false;
				z->parent->parent->color=1;
				z=z->parent->parent;								//z moves up 2 levels
			}

			else if(z==z->parent->left)								//z is a left child
			{
				z=z->parent;
				rightRotate(z);
			}
			
			else
			{
				z->parent->color=false;			
				z->parent->parent->color=true;			
				leftRotate(z->parent->parent);
			}
		}															//End of else

	}																//End of while loop
	root->color=false;
}


void RedBlack::Transplant(node* u, node* v)
{
	if(u->parent==NIL)
	{
		root=v;
	}
	else if(u==u->parent->left)										//u is a left child
		u->parent->left=v;
	else															//u is a right child
		u->parent->right=v;

	v->parent=u->parent;
}

void RedBlack::del(node* z)
{
	node* y=z;
	node* x;
	bool remcol=y->color;
	if(z->left==NIL)
	{
		x=z->right;
		Transplant(z,z->right);
	}

	else if(z->right==NIL)
	{
		x=z->left;
		Transplant(z,z->left);
	}

	else
	{
		y=succ(z);
		remcol=y->color;
		x=y->right;
		if(y->parent==z)
			x->parent=y;

		else
		{
			Transplant(y,y->right);
			y->right=z->right;
			y->right->parent=y;
		}
		Transplant(z,y);
		y->left=z->left;
		y->left->parent=y;
		y->color=z->color;
	}
	if(remcol==black)
		delfix(x);
	size--;
}

void RedBlack::delfix(node* x)
{
	while(x!=root && !x->color)
	{
		node* w;
		if(x==x->parent->left)										//x is a left child
		{
			w=x->parent->right;										//w is the sibling of x
			if(w->color)											//CASE 1
			{
				w->color=black;
				x->parent->color=red;
				leftRotate(x->parent);
				w=x->parent->right;
			}														//end of CASE 1
			if(!w->left->color && !w->right->color)
			{
				w->color=red;										//CASE 2
				x=x->parent;										//CASE 2
			}
			else if(!(w->right->color))								//CASE 3
			{
				w->left->color=black;
				w->color=red;
				rightRotate(w);
				w=x->parent->right;
			}														//End of CASE 3
			w->color=x->parent->color;								//CASE 4
			x->parent->color=black;									//CASE 4
			leftRotate(x->parent);									//CASE 4
			x=root;
		}
		else														//x is a right child
		{
			w=x->parent->left;										//w is the sibling of x
			if(w->color)
			{
				w->color=black;
				x->parent->color=red;
				rightRotate(x->parent);
				w=x->parent->left;
			}
			if(!w->left->color && !w->right->color)
			{
				w->color=red;
				x=x->parent;
			}
			else if(!(w->left->color))
			{
				w->right->color=black;
				w->color=red;
				leftRotate(w);
				w=x->parent->left;
			}
			w->color=x->parent->color;
			x->parent->color=black;
			rightRotate(x->parent);
			x=root;
		}
	}																//end of while loop
	x->color=black;
}
node* RedBlack::search(int k)
{
	node *y=root;
	while(y!=NIL)
	{
		if((y->key)>k)
		{
			y=y->left;
		}
		else if((y->key)<k)
			y=y->right;
		else
			return y;
	}
	return NIL;
}
void RedBlack::inorder(node *z)
{
	if(z!=NIL)
	{
		inorder(z->left);
		cout<<"("<<z->key<<",";
		if(z->color)
		{
			cout<<"red) ";
		}
		else
		{
			cout<<"black) ";
		}
		inorder(z->right);
	}
}
void RedBlack::preorder(node *z)
{
	if(z!=NIL)
	{
		cout<<"("<<z->key<<",";
		if((z->color)==1)
		{
			cout<<"red) ";
		}
		else
		{
			cout<<"black) ";
		}
		node** t=spine(root);
		for(int i=0;t[i]!=NIL;t++)
		{
			if(z==t[i])
			{
				cout<<'\n';
				break;
			}
		}
		preorder(z->left);
		cout<<' ';
		preorder(z->right);	
	}
}
void RedBlack::postorder(node *z)
{
	if(z!=NIL)
	{
		postorder(z->left);
		cout<<'\t';
		postorder(z->right);
		cout<<"("<<z->key<<",";
		if((z->color)==1)
		{
			cout<<"red)\n ";
		}
		else
		{
			cout<<"black)\n ";
		}
	}
}
node* RedBlack::TreeMin(node *z)
{
	node *y=z;
	while(y->left!=NIL)
	{
		y=y->left;
	}
	return y;
}
node* RedBlack::succ(node *z)
{
	node *y,*x;
	if((z->right)!=NIL)
	{
		y=(z->right);
		while(y!=NIL)
		{
			x=y;
			y=y->left;
		}
		return x;
	}
	else
	{
		y=z->parent;
		while(y!=NIL&&z==(y->right))
		{
			z=y;
			y=y->parent;
		}
		return y;
	}
}
node* RedBlack::pred(node *z)
{
	node *y,*x;
	if((z->left)!=NIL)
	{
		y=(z->left);
		while(y!=NIL)
		{
			x=y;
			y=y->right;
		}
		return x;
	}
	else
	{
		y=z->parent;
		while(y!=NIL&&z==(y->left))
		{
			z=y;
			y=y->parent;
		}
		return y;
	}
}
node** RedBlack:: spine(node* z)
{
	node** x;
	x=new node*[size];
	int i=0;
	while(z!=NIL)
	{
		x[i++]=z;
		z=z->right;
	}
	x[i]=NIL;
	return x;
}
