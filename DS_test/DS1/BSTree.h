#include "utili.h"

/*¶þ²æÅÅÐòÊ÷*/
typedef int DataType;

typedef struct BSTNode
{
	DataType data;
	BSTNode *leftChild;
	BSTNode *rightChild;
}BSTNode;

typedef struct BSTree
{
	BSTNode* root;
}BSTree;

void init_bst(BSTree *bt);
bool	insert(BSTree *bt, DataType x);
bool insert(BSTNode *&rt, DataType x);

BSTNode* max(BSTree *bt);
BSTNode* max(BSTree *bt, BSTNode *rt);
BSTNode* min(BSTree *bt);
BSTNode* min(BSTree *bt, BSTNode *rt);

bool remove(BSTree *bt, DataType x);
bool remove(BSTNode *&bt, DataType x);

void inorder(BSTree *bt);
void inorder(BSTNode *t);

BSTNode* find(BSTree *bt, DataType x);
BSTNode* find(BSTNode *rt, DataType x);

void init_bst(BSTree *bst)
{
	bst->root = NULL;
}

bool insert(BSTree *bt, DataType x)	{	return insert( bt->root, x);	}
bool insert(BSTNode *&rt, DataType x)
{
	if (rt == NULL)
	{
		rt = (BSTNode *)malloc(sizeof(BSTNode));
		assert(rt != NULL);
		rt->data = x;
		rt->leftChild = rt->rightChild = NULL;
	}
	else if (x > rt->data)
		insert(rt->rightChild, x);
	else if (x < rt->data)
		insert(rt->leftChild, x);
	else
		return false;

	return true;
}

BSTNode* max(BSTree *bt)	{	return max(bt, bt->root);	}
BSTNode* max(BSTree *bt, BSTNode *rt)
{
	if (rt != NULL)
	{
		while (rt->rightChild != NULL)
			rt = rt->rightChild;

		return rt;
	}
}

BSTNode* min(BSTree *bt)	{	return min(bt, bt->root);	}
BSTNode* min(BSTree *bt, BSTNode *rt)
{
	if (rt != NULL)
	{
		while (rt->leftChild != NULL)
			rt = rt->leftChild;

		return rt;
	}
}

bool remove(BSTree *bt, ElemType x)	{	return remove(bt->root, x);	 }
bool remove(BSTNode *&rt, DataType x)
{
	if (t == NULL)
		return false;
	if (x < rt->data)
		remove(t->leftChild, x);
	else if (x > rt->data)
		remove(rt->rightChild, x);
	else
	{
		BSTNode *p = NULL;
		if (rt->leftChild != NULL && rt->rightChild != NULL)
		{
			p = rt->rightChild;
			while (p->leftChild != NULL)
				p = p->leftChild;
			rt->data = p->data;
			remove(t->rightChild, p->data);
		}
		else
		{
			p = rt;
			if (rt->leftChild == NULL)
				rt = rt->rightChild;
			else
				rt = rt->leftChild;
			
			free(p);
			p = NULL;
		}
	}
}

void inorder(BSTree *bt)	{ inorder(bt->root); }
void inorder(BSTNode *t)
{
	if (t != NULL)
	{
		inorder(t->leftChild);
		cout << t->data << " ";
		inorder(t->rightChild);
	}
}

BSTNode* find(BSTree *bt, DataType x)		{ return find(bt->root, x);	 }
BSTNode* find(BSTNode *rt, DataType x)
{
	if (rt == NULL)
		return NULL;
	else if (rt->data == x)
		return rt;
	else if (rt->data > x)
		return find(rt->leftChild, x);
	else
		return find(rt->rightChild, x);
}

/*
bool remove(BSTNode *&t, ElemType key)
{
	if (t == NULL)
		return FALSE;
	if (key < t->data)
		remove(t->leftChild, key);
	else if (key > t->data)
		remove(t->rightChild, key);
	else
	{
		BSTNode *p = NULL;
		if (t->leftChild == NULL && t->rightChild == NULL)
		{
			free(t);
			t = NULL;
		}
		else if (t->leftChild != NULL && t->rightChild == NULL)
		{
			p = t;
			t = t->leftChild;
			free(p);
		}
		else if (t->leftChild == NULL && t->rightChild != NULL)
		{
			p = t;
			t = t->rightChild;
			free(p);
		}
		else
		{
			p = t->rightChild;
			while (p->leftChild != NULL)
				p = p->leftChild;
			t->data = p->data;
			remove(t->rightChild, p->data);
		}
	}
	return TRUE;
}
*/