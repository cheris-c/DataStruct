/*
		现在有一个用来存放整数的Hash表，Hash表的存储单位称为桶，每个桶能放3个整数，当一个桶中
要放的元素超过3个时，则要将新的元素存放在溢出桶中，每个溢出桶也能放3个元素，多个溢出
桶使用链表串起来。此Hash表的基桶数目为素数P，Hash表的hash函数对P取模
*/

#include<iostream>
using namespace std;

#define P 7
#define BUCKET_NODE_SIZE 3
#define NULL_DATA -1

typedef struct _bucket_node	
{
	int data[BUCKET_NODE_SIZE];
	struct _bucket_node *next;
}bucket_node;

typedef  bucket_node   hash_table[P];		 //hash_table 表示有P个bucket_node类型的数组
hash_table ht;

void init_hashtable(hash_table &h)
{
	for(int i=0; i<P; ++i)
	{
		for(int j=0; j<BUCKET_NODE_SIZE; ++j)
		{
			h[i].data[j] = NULL_DATA;
		}
		h[i].next = NULL;
	}
}

//按照除留余数法，每次将节点插入对应的索引位置，当当前节点的数组已满时，创建新的的节点，并与原节点链接起来。
bool insert_new_element(hash_table &h, int x)
{
	int index = x % P;
	bucket_node *p = &h[index];

	//将p指向当前索引在哈希表中最后一个节点，因为前几个节点肯定都存满了
	while (p->next != NULL)
	{
		p = p->next;
	}

	//最后一个节点未满，接着存放数据
	if (p->data[BUCKET_NODE_SIZE - 1] == NULL_DATA)
	{
		for (int i = 0; i < BUCKET_NODE_SIZE; ++i)
		{
			if (p->data[i] == NULL_DATA)
			{
				p->data[i] = x;
				return true;
			}																												 
		}
	}
	else  //最后一个节点已满，创建新节点
	{
		bucket_node *node = (bucket_node *)malloc(sizeof(bucket_node));
		if (NULL == node)
		{
			cout << "生成节点失败" << endl;
			return false;
		}

		for (int i = 0; i < BUCKET_NODE_SIZE; ++i)
		{
			node->data[i] = NULL_DATA;
		}
		
		node->next = NULL;
		p->next = node;
		for (int i = 0; i < BUCKET_NODE_SIZE; ++i)
		{
			if (node->data[i] == NULL_DATA)
			{
				node->data[i] = x;
				return true;
			}
		}
	}

	return false;
}

int main()
{
	init_hashtable(ht);
	int array[] = {15,14,21,87,96,293,35,24,149,19,63,16,103,77,5,153,145,356,51,68,705,453 };  
	//int array[] = {1, 8, 15, 22, 29, 36, 43, 50};

	int n = sizeof(array) / sizeof(int);
	for(int i=0; i<n; ++i)
	{
		insert_new_element(ht,array[i]);
	}

	bucket_node *p = NULL;
	for (int i = 0; i < P; ++i)
	{
		cout << i << " : ";
		p = &ht[i];
		while (p != NULL)
		{
			if (p->data[0] != NULL_DATA)
			{
				for (int i = 0; i < BUCKET_NODE_SIZE; ++i)
				{
					if (p->data[i] != NULL_DATA)
						cout << p->data[i] << "  ";
				}
			} //if

			p = p->next;
		} //while
		cout << endl;
	} //for

	system("pause");
	return 0;
}
