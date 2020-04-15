/*
二叉树的简单实现
测试数据：
输入：ABC##DE##F##G#H##
*/
#include <assert.h>
#include <iostream>
#include <queue>

using namespace std;

typedef char ElemType;

typedef struct BinTreeNode
{
	ElemType data;
	BinTreeNode *leftNode;
	BinTreeNode *rightNode;
}BinTreeNode;

typedef struct BinTree
{
	BinTreeNode *root;
	ElemType refval;
}BinTree;

void init_tree(BinTree *t, ElemType data);
void create_tree(BinTree *bt);
void create_tree(BinTree *bt, BinTreeNode **root);

void preOrder(BinTree *bt, BinTreeNode *root);				//DLR
void inOrder(BinTree *bt, BinTreeNode *root);				//LDR
void postOrder(BinTree *bt, BinTreeNode *root);			    //LRD
void levelOrder(BinTree *bt, BinTreeNode *root);			//层序遍历

int size(BinTree *bt, BinTreeNode *root);
int height(BinTree *bt, BinTreeNode *root);

BinTreeNode* find(BinTree *bt, ElemType x);
BinTreeNode* find(BinTreeNode *root, ElemType x);
BinTreeNode* parent(BinTree *bt, ElemType x);
BinTreeNode* parent(BinTreeNode *root, ElemType x);

void destroy_tree(BinTree *bt, BinTreeNode *root);

int main()
{
	BinTree *bt = new BinTree();

	init_tree(bt, '#');			//将'#'符号设为一个结点是否为空的基准，输入#号代表该结点为空
	cout << "Please input Binary_Tree Order(ABC##DE##F##G#H##) :" << endl;
	create_tree(bt);

	cout << "szie : " << size(bt, bt->root) << endl;
	cout << "height : " << height(bt, bt->root) << endl;

	BinTreeNode *temp = find(bt, 'A');
	cout << temp->data << endl;
	temp = parent(bt, 'B');
	cout << temp->data << endl;

	cout << "DLR : ";
	preOrder(bt, bt->root);
	cout << endl;

	cout << "LDR : ";
	inOrder(bt, bt->root);
	cout << endl;

	cout << "LDR : ";
	postOrder(bt, bt->root);
	cout << endl;

	cout << "Level Order: ";
	levelOrder(bt, bt->root);
	cout << endl;

	destroy_tree(bt, bt->root);
	return 0;
}

void init_tree(BinTree *bt, ElemType data)
{
	bt->refval = data;				//为通过输入的数据判断当前结点是否为空设置一个判断标准。
	bt->root = NULL;
}


//输入的格式为:ABC####	（#号的个数和顺序对应二叉树的创建顺序并且当前结点保存的数据为空）
/*
ABC####
代表A的左结点为B,B的左结点为C，C的左右结点、B的右节点、A的右节点都为空。所有有四个'#'。
只有输入的数据个数满足要求的数据个数时递归才会结束 。
*/
void create_tree(BinTree *bt)
{
	create_tree(bt, &(bt->root));
}
void create_tree(BinTree *bt, BinTreeNode **root)
{
	char item;
	cin >> item;

	if (item == bt->refval)
	{
		*root = NULL;
	}
	else
	{
		*root = (BinTreeNode *)malloc(sizeof(BinTreeNode));
		assert(*root != NULL);
		(*root)->data = item;

		create_tree(bt, &((*root)->leftNode));
		create_tree(bt, &((*root)->rightNode));
	}
}

void preOrder(BinTree *bt, BinTreeNode *root)
{
	if (root != NULL)
	{
		cout << root->data << "  ";
		preOrder(bt, root->leftNode);
		preOrder(bt, root->rightNode);
	}
}

void inOrder(BinTree *bt, BinTreeNode *root)
{
	if (root != NULL)
	{
		inOrder(bt, root->leftNode);
		cout << root->data << "  ";
		inOrder(bt, root->rightNode);
	}
}

void postOrder(BinTree *bt, BinTreeNode *root)
{
	if (root != NULL)
	{
		inOrder(bt, root->leftNode);
		inOrder(bt, root->rightNode);
		cout << root->data << "  ";
	}
}

void levelOrder(BinTree *bt, BinTreeNode *root)
{
	BinTreeNode *curPtr = root;
	queue<BinTreeNode *> level;

	if (curPtr == NULL)
		return;

	level.push(curPtr);
	while (!level.empty())
	{
		curPtr = level.front();
		cout << curPtr->data << " ";
		level.pop();

		if (curPtr->leftNode != NULL)
			level.push(curPtr->leftNode);
		if (curPtr->rightNode != NULL)
			level.push(curPtr->rightNode);
	}
}

int size(BinTree *bt, BinTreeNode *root)
{
	if (NULL == root)
		return 0;
	else
		return size(bt, root->leftNode) + size(bt, root->rightNode) + 1;
}

int height(BinTree *bt, BinTreeNode *root)
{
	if (NULL == root)
		return 0;
	else
	{
		int left_height = height(bt, root->leftNode);
		int right_height = height(bt, root->rightNode);
		return (left_height > right_height ? left_height : right_height) + 1;
	}
}

BinTreeNode *find(BinTree *bt, ElemType x)
{
	return find(bt->root, x);
}
BinTreeNode *find(BinTreeNode *root, ElemType x)
{
	if (NULL == root)
		return NULL;
	if (root->data == x)
		return root;

	BinTreeNode *p = find(root->leftNode, x);
	if (NULL != p)
		return p;
	return find(root->rightNode, x);
}

BinTreeNode* parent(BinTree *bt, ElemType x)
{
	return parent(bt->root, x);
}
BinTreeNode* parent(BinTreeNode *root, ElemType x)
{
	if (root == NULL)
		return NULL;

	BinTreeNode *p = find(root, x);
	if (p == NULL || p == root)
		return NULL;
	if (root->leftNode == p || root->rightNode == p)
		return root;

	p = parent(root->leftNode, x);
	if (p != NULL)
		return p;

	return parent(root->rightNode, x);
}

void destroy_tree(BinTree *bt, BinTreeNode *root)
{
	if (root != NULL)
	{
		destroy_tree(bt, root->leftNode);
		destroy_tree(bt, root->rightNode);

		delete root;
		root = NULL;
	}
}