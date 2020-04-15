#pragma once

#include"utili.h"

typedef struct BSTNode
{
	ElemType data;
	BSTNode *leftChild;
	BSTNode *rightChild;
}BSTNode;

typedef struct BSTree
{
	BSTNode *root;
}BSTree;

void init_bst(BSTree *bst);
BOOL insert(BSTree *bst, ElemType x);
BOOL insert(BSTNode *&t, ElemType x);
ElemType max(BSTree *bst);
ElemType max(BSTNode *t);
ElemType min(BSTree *bst);
ElemType min(BSTNode *t);
void sort(BSTree *bst);
void sort(BSTNode *t);
BOOL remove(BSTree *bst, ElemType key);
BOOL remove(BSTNode *&t, ElemType key);
BSTNode* find(BSTree *bst, ElemType key);
BSTNode* find(BSTNode *t, ElemType key);

void init_bst(BSTree *bst)
{
	bst->root = NULL;
}

BOOL insert(BSTree *bst, ElemType x)
{
	return insert(bst->root, x);
}
BOOL insert(BSTNode *&t, ElemType x)
{
	if(t == NULL)
	{
		t = (BSTNode*)malloc(sizeof(BSTNode));
		assert(t != NULL);
		t->data = x;
		t->leftChild = t->rightChild = NULL;
		return TRUE;
	}
	else if(x > t->data)
	{
		insert(t->rightChild, x);
	}
	else if(x < t->data)
	{
		insert(t->leftChild, x);
	}

	return FALSE;
}

ElemType max(BSTree *bst)
{
	return max(bst->root);
}
ElemType max(BSTNode *t)
{
	if(t != NULL)
	{
		while(t->rightChild != NULL)
			t = t->rightChild;
		return t->data;
	}
}
ElemType min(BSTree *bst)
{
	return min(bst->root);
}
ElemType min(BSTNode *t)
{
	if(t != NULL)
	{
		while(t->leftChild != NULL)
			t = t->leftChild;
		return t->data;
	}
}

void sort(BSTree *bst)
{
	sort(bst->root);
}
void sort(BSTNode *t)
{
	if(t != NULL)
	{
		sort(t->leftChild);
		cout<<t->data<<" ";
		sort(t->rightChild);
	}
}

BOOL remove(BSTree *bst, ElemType key)
{
	return remove(bst->root, key);
}

BOOL remove(BSTNode *&t, ElemType key)
{
	if(t == NULL)
		return FALSE;
	if(key < t->data)
		remove(t->leftChild, key);
	else if(key > t->data)
		remove(t->rightChild, key);
	else
	{
		BSTNode *p = NULL;
		if(t->leftChild!=NULL && t->rightChild!=NULL)
		{
			p = t->rightChild;
			while(p->leftChild != NULL)
				p = p->leftChild;
			t->data = p->data;
			remove(t->rightChild, p->data);
		}
		else
		{
			p = t;
			if(t->leftChild == NULL)
				t = t->rightChild;
			else
				t = t->leftChild;
			free(p);
			p = NULL;
		}
	}
}

BSTNode* find(BSTree *bst, ElemType key)
{
	return find(bst->root, key);
}
BSTNode* find(BSTNode *t, ElemType key)
{
	if(t == NULL)
		return NULL;
	else if(t->data == key)
		return t;
	else if(t->data > key)
		return find(t->leftChild, key);
	else 
		return find(t->rightChild, key);
}

/*
BOOL remove(BSTNode *&t, ElemType key)
{
	if(t == NULL)
		return FALSE;
	if(key < t->data)
		remove(t->leftChild, key);
	else if(key > t->data)
		remove(t->rightChild, key);
	else
	{
		BSTNode *p = NULL;
		if(t->leftChild==NULL && t->rightChild==NULL)
		{
			free(t);
			t = NULL;
		}
		else if(t->leftChild!=NULL && t->rightChild==NULL)
		{
			p = t;
			t = t->leftChild;
			free(p);
		}
		else if(t->leftChild==NULL && t->rightChild!=NULL)
		{
			p = t;
			t = t->rightChild;
			free(p);
		}
		else
		{
			p = t->rightChild;
			while(p->leftChild != NULL)
				p = p->leftChild;
			t->data = p->data;
			remove(t->rightChild, p->data);
		}
	}
	return TRUE;
}
*/