#include<iostream>
#include"config.h"
#include"stack.h"
#include"queue.h"
//#include"tree.h"
//#include"threadbintree.h"
#include "bstree.h"

using namespace std;

void main()
{
	int arr[] = {45, 12, 90, 37, 3, 53, 100, 61, 24, 78};
	BSTree bt;
	init_bst(&bt);
	for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		insert(&bt, arr[i]);
	}

	inorder(&bt);
	cout << endl;
}

#if 0
void main()
{
	const char *str = "ABC##DE##F##G#H##";
	BinTree bt;
	init_tree(&bt);
	create_tree(&bt, str);
	create_inthread(&bt);
	BinTreeNode *p = first(&bt);
	p = next(&bt, p);
	p = next(&bt, p);
	//p = next(&bt, p);
	BinTreeNode *pr = parent(&bt, p);
	//BinTreeNode *q = prio(&bt, p);

	//inorder(&bt);
	//p = last(&bt);
}
#endif

/*
void main()
{
	char *str = "ABC##DE##F##G#H##";
	//char *str = "AB#C##D##";
	BinTree bt;
	init_tree(&bt, '#');
	create_tree(&bt,str);
	cout<<"VLR:";
	preorder_1(&bt);
	cout<<endl;
	//cout<<"LVR:";
	//inorder(&bt);
	//cout<<endl;
	//cout<<"LRV:";
	//postorder(&bt);
	//cout<<endl;
}

/*
void main()
{
	char *str = "ABC##DE##F##G#H##";
	//char *str = "AB#C##D##";
	BinTree bt;
	init_tree(&bt, '#');
	create_tree(&bt,str);

	cout<<"size = "<<size(&bt)<<endl;
	cout<<"height = "<<height(&bt)<<endl;
	BinTreeNode *p = find(&bt, 'H');
	BinTreeNode *pr = parent(&bt, 'H');
	destroy_tree(&bt);
}


/*
void main()
{
	char *VLR = "ABCDEFGH";
	char *LVR = "CBEDFAGH";
	char *LRV = "CEFDBHGA";
}

/*
void main()
{
	char *str = "ABC##DE##F##G#H##";
	BinTree bt;
	init_tree(&bt, '#');
	create_tree(&bt,str);

	cout<<"VLR:";
	preorder(&bt);
	cout<<endl;
	cout<<"LVR:";
	inorder(&bt);
	cout<<endl;
	cout<<"LRV:";
	postorder(&bt);
	cout<<endl;
}

/*
void main()
{
	Queue Q;
	init_queue(&Q);
	enqueue(&Q,1);
	enqueue(&Q,2);
	enqueue(&Q,3);
	enqueue(&Q,4);
	enqueue(&Q,5);
	enqueue(&Q,6);
	enqueue(&Q,7);

	dequeue(&Q);

	enqueue(&Q,8);
	enqueue(&Q,9);
	show_queue(&Q);
	cout<<"------------"<<endl;


}

/*
bool Check(char *exp)
{
	//
}

//int Exp()

void main()
{
	char *str = "([()][()])";
	bool flag = Check(str);
	if(flag)
	{
		cout<<"OK."<<endl;
	}
	else
	{
		cout<<"Error."<<endl;
	}
}

/*
void Convert_2(int val)
{
	Stack st;
	init_stack(&st);
	while(val)
	{
		push(&st, val%2);
		val /= 2;
	}
	show_stack(&st);
}

void main()
{
	unsigned int val;
	cout<<"input value:>";
	cin>>val;
	Convert_2(val);
}

/*
char* Convert_2(unsigned int val)
{	static char buffer[sizeof(int)*8+1]; //
	int mod;
	for(int i=sizeof(int)*8-1; i>=0; --i)
	{
		mod = val % 2;
		buffer[i] = mod + '0';
		val /= 2;
	}
	return  buffer;
}

char* Convert_16(unsigned int val)
{	
	static char buffer[sizeof(int)*2+1]; //
	int mod;
	for(int i=sizeof(int)*2-1; i>=0; --i)
	{
		buffer[i] = "0123456789ABCDEF"[val % 16];
		val /= 16;
	}
	return  buffer;
}

void main()
{
	unsigned int val;
	cout<<"input value:>";
	cin>>val;
	cout<<Convert_16(val)<<endl;
}

/*

char* Convert_16(unsigned int val)
{	static char buffer[sizeof(int)*2+1]; //
	int mod;
	for(int i=sizeof(int)*8-1; i>=0; --i)
	{
		mod = val % 16;
		if(mod >= 10)
		{
			buffer[i] = 'A'+mod-10;
		}
		else
		{
			buffer[i] = mod + '0';
		}
		val /= 16;
	}
	return  buffer;
}
#ifdef STACK
#include"stack.h"

int main()
{
	Stack st;
	init_stack(&st);
	push(&st,1);
	push(&st,2);
	push(&st,3);
	push(&st,4);
	push(&st,5);
	show_stack(&st);
	cout<<"==========="<<endl;
	cout<<gettop(&st)<<" 出栈"<<endl;
	//pop(&st);
	cout<<gettop(&st)<<" 出栈"<<endl;
	//pop(&st);
	show_stack(&st);

	destroy_stack(&st);
	return 0;
}

#else

#ifdef SEQLIST
#include"seqlist.h"
#endif

#ifdef LIST
#include"list.h"
#endif

int main()
{
	ElemType item;
	int pos;
	int len;
#ifdef LIST
	ListNode *p = NULL;
#endif


	List mylist;
	init_list(&mylist);
	int select = 1;
	while(select)
	{
		system("cls");
		cout<<"************************************"<<endl;
		cout<<"* [1] push_back    [2] push_front  *"<<endl;
		cout<<"* [3] show_list    [0] quit_system *"<<endl;
		cout<<"* [4] pop_back     [5] pop_front   *"<<endl;
		cout<<"* [6] insert_pos   [7] insert_val  *"<<endl;
		cout<<"* [8] erase_pos    [9] erase_val   *"<<endl;
		cout<<"* [10] find        [11] sort       *"<<endl;
		cout<<"* [12] length      [13] clear      *"<<endl;
		cout<<"* [14] reverse                     *"<<endl;
		cout<<"************************************"<<endl;
		cout<<"请选择:>";
		cin>>select;
		switch(select)
		{
		case 1:
			cout<<"请输入要插入的数据<-1结束>:>";
			while(cin>>item, item!=-1)
			{
				push_back(&mylist, item);
			}
			break;
		case 2:
			cout<<"请输入要插入的数据<-1结束>:>";
			while(cin>>item, item!=-1)
			{
				//push_front(&mylist, item);
			}
			break;
		case 3:
			show_list(&mylist);
			break;
		case 4:
			//pop_back(&mylist);
			break;
		case 5:
			//pop_front(&mylist);
			break;
		case 6:
			cout<<"请输入要插入的数据:>";
			cin>>item;
			cout<<"请输入要查入的位置:>";
			cin>>pos;
			//insert(&mylist, pos, item);
			break;
		case 7:
			cout<<"请输入要插入的数据:>";
			cin>>item;
			insert(&mylist, item);
			break;
		case 8:
			cout<<"请输入要删除的位置:>";
			cin>>pos;
			//erase(&mylist, pos);
			break;
		case 9:
			cout<<"请输入要删除的值:>";
			cin>>item;
			erase_val(&mylist, item);
			break;
		case 10:
			cout<<"请输入要查找的值:>";
			cin>>item;
#ifdef SEQLIST
			pos = find(&mylist, item);
			cout<<"pos = "<<pos<<endl;
#endif

#ifdef LIST
			//p = find(&mylist, item);
#endif
			break;
		case 12:
			//len = length(&mylist);
			cout<<"length = "<<len<<endl;
			break;
		case 11:
			//sort(&mylist);
			break;
		case 13:
			//clear(&mylist);
			break;
		case 14:
			//revserse(&mylist);
			break;
		default:
			break;
		}
		
		system("pause");
		
	}
	//destroy(&mylist);
	
	return 0;
}
#endif
*/