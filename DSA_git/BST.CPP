
#include "iostream.h"
#include "conio.h"
class NODE
{
	public:
		int data;
		NODE *left, *right;
};
class TREE
{
		//  data
	public:
		NODE *root;
		// operations
		TREE();
		void ADD(int); 	// 1
		void DEL(int);  // 2
		void PRE_ORD(NODE *); // 3
		void IN_ORD(NODE *); 	// 4
		void POST_ORD(NODE *);// 5
		NODE * FIND_IIO_SUCCESSOR(NODE *);
		void MENU();
};
/////////////////////////////////////////////////////////////////
TREE::TREE()
{
	// def of function
	root = NULL;
}
/////////////////////////////////////////////////////////////////
void TREE::ADD(int ele)
{
	// def of function
	//----- (A) create new node --------------
	NODE *NN;
	NN= new NODE(); // allocate new node
	//----- (B) fill up new node -------------
	NN->data = ele;
	NN->left = NULL;
	NN->right = NULL;
	//---- (C) set the links -----------------
	if(root==NULL) //case - II Not Full - Empty
		root=NN;
	else //case - III Not Full - Not Empty
	{
		NODE *par = NULL;
		NODE *ptr = root;
		while(ptr != NULL)
		{
			par = ptr;
			if(ele < ptr->data)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		if(ele < par->data)
			par->left = NN;
		else
			par->right = NN;
	}
}
/////////////////////////////////////////////////////////////////
NODE * TREE:: FIND_IIO_SUCCESSOR(NODE *ptr)
{
	NODE *par_ssr = ptr;
	NODE *ssr = ptr->right;
	while(ssr->left != NULL)
	{
		par_ssr = ssr;
		ssr = ssr->left;
	}
	// delete ssr
	if(par_ssr == ptr)
		par_ssr->right = ssr->right;
	else
		par_ssr->left = ssr->right;
	return ssr;
}
/////////////////////////////////////////////////////////////////
void TREE::DEL(int ele)
{
	if(root == NULL)
		cout<<endl<<"Tre is empty";
	else // Tree not empty
	{
		NODE *ptr=root;
		NODE *par=NULL;
		// find the node to be deleted with his parent
		while(ptr!=NULL)
		{
			if(ptr->data==ele)
				break; // node found
			else
			{
				par = ptr;
				if(ele<ptr->data)
					ptr=ptr->left;
				else
					ptr=ptr->right;
			 }
		}
		if(ptr == NULL) // node not found
			cout<<"Element Not Found";
		else // node found
		{
			NODE *TEMP=ptr;
			if(ptr->left==NULL && ptr->right==NULL) // zero  child
			{
				if(par == NULL) // ptr is root of tree
					root = NULL;
				else
					if(ele<par->data)
						par->left=NULL;
					else
						par->right=NULL;
			}
			else
			{
				if(ptr->left == NULL || ptr->right == NULL) // 1 child
				{
					// find out child
					NODE *ch;
					if(ptr->left==NULL)
						ch = ptr->right;
					else
						ch=ptr->left;
					// set links
					if(par == NULL) // ptr is root of tree
						root  = ch;
					else
					{
						if(ele<par->data)
							par->left=ch;
						else
							par->right=ch;
					}
				}
				else // 2 children
				{
					NODE *IIOS = FIND_IIO_SUCCESSOR(ptr);

					IIOS->left = ptr->left;
					IIOS->right = ptr->right;

					if( ele < par->data )
						par->left = IIOS;
					else
						par->right = IIOS;
				}
			}
			delete TEMP;
		}
	}
}
/////////////////////////////////////////////////////////////////
void TREE::PRE_ORD( NODE *ptr)
{
	// def of function
	if(ptr != NULL)
	{
		cout<<ptr->data<<" ";
		PRE_ORD(ptr->left);
		PRE_ORD(ptr->right);
	}
}
/////////////////////////////////////////////////////////////////
void TREE::IN_ORD( NODE *ptr)
{
	// def of function
	if(ptr != NULL)
	{
		IN_ORD(ptr->left);
		cout<<ptr->data<<" ";
		IN_ORD(ptr->right);
	}
}
/////////////////////////////////////////////////////////////////
void TREE::POST_ORD( NODE *ptr)
{
	// def of function
	if(ptr != NULL)
	{
		POST_ORD(ptr->left);
		POST_ORD(ptr->right);
		cout<<ptr->data<<" ";
	}
}
/////////////////////////////////////////////////////////////////
void TREE::MENU()
{
	int ele, opt;
	do
	{
		cout<<endl<<"================\n";
		cout<<endl<<"1 Add Node";
		cout<<endl<<"2 Delete Node";
		cout<<endl<<"3 Pre-Order Traversal";
		cout<<endl<<"4 In-Order Traversal";
		cout<<endl<<"5 Post-Order Traversal";
		cout<<endl<<"6 Exit";
		cout<<endl<<"================\n";
		cout<<endl<<"Enter your choice : ";
		cin>>opt;
		switch(opt)
		{
			case 1:
				cout<<endl<<"Enter element : ";
				cin>>ele;
				ADD(ele);
				IN_ORD(root);
				break;
			case 2:
				cout<<endl<<"Enter element : ";
				cin>>ele;
				DEL(ele);
				if(root != NULL)
					IN_ORD(root);
				else
					cout<<endl<<"Tree empty";
				break;
			case 3:
				if(root != NULL)
					PRE_ORD(root);
				else
					cout<<endl<<"Tree empty";
				break;
			case 4:
				if(root != NULL)
					IN_ORD(root);
				else
					cout<<endl<<"Tree empty";
				break;
			case 5:
				if(root != NULL)
					POST_ORD(root);
				else
					cout<<endl<<"Tree empty";
				break;
			case 6:
				return;
			default:
				cout<<endl<<"Invalid input";
		}
	}while(1);
}
/////////////////////////////////////////////////////////////////
void main()
{
	TREE obj;
	clrscr();
	obj.MENU();
	getch();
}
/////////////////////////////////////////////////////////////////
