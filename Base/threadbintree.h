#pragma once

#include"utili.h"

typedef enum{LINK,THREAD}Type_Tag;

typedef struct BinTreeNode
{
	ElemType data;
	BinTreeNode *leftChild;
	BinTreeNode *rightChild;
	Type_Tag ltag;
	Type_Tag rtag;
}BinTreeNode;

typedef struct BinTree
{
	BinTreeNode *root;
	ElemType     refval;
}BinTree;

BinTreeNode* _Buynode(ElemType x);
void init_tree(BinTree *bt);
void create_tree(BinTree *bt, const char *str);
void create_tree(BinTree *bt, BinTreeNode *&t, const char *&str);
void create_inthread(BinTree *bt);
void create_inthread(BinTreeNode *&t, BinTreeNode *&pre);

/////////////////////////////////////////////////////////////////
BinTreeNode* first(BinTree *bt);
BinTreeNode* first(BinTreeNode *t);
BinTreeNode* last(BinTree *bt);
BinTreeNode* last(BinTreeNode *t);
BinTreeNode* next(BinTree *bt, BinTreeNode *cur);
BinTreeNode* next(BinTreeNode *t, BinTreeNode *cur);
BinTreeNode* prio(BinTree *bt, BinTreeNode *cur);
BinTreeNode* prio(BinTreeNode *t, BinTreeNode *cur);
void inorder(BinTree *bt);
void inorder(BinTreeNode *bt);
BinTreeNode* parent(BinTree *bt, BinTreeNode *cur);
BinTreeNode* parent(BinTreeNode *t, BinTreeNode *cur);

BinTreeNode* _Buynode(ElemType x)
{
	BinTreeNode *s = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	assert(s != NULL);
	s->data = x;
	s->ltag = s->rtag = LINK;
	s->leftChild = s->rightChild = NULL;
	return s;
}
void init_tree(BinTree *bt)
{
	bt->root = NULL;
	bt->refval = '#';
}

void create_tree(BinTree *bt, const char *str)
{
	create_tree(bt, bt->root, str);
}
void create_tree(BinTree *bt, BinTreeNode *&t, const char *&str)
{
	if(*str=='\0' || *str==bt->refval)
		t = NULL;
	else
	{
		t = _Buynode(*str);
		create_tree(bt,t->leftChild, ++str);
		create_tree(bt,t->rightChild,++str);
	}
}

void create_inthread(BinTree *bt)
{
	BinTreeNode *pre = NULL;
	create_inthread(bt->root, pre);
	pre->rightChild = NULL;
	pre->rtag = THREAD;

}
void create_inthread(BinTreeNode *&t,BinTreeNode *&pre)
{
	if(t == NULL)
		return;
	create_inthread(t->leftChild, pre);
	if(t->leftChild == NULL)
	{
		t->ltag = THREAD;
		t->leftChild = pre;
	}
	if(pre!=NULL && pre->rightChild==NULL)
	{
		pre->rtag = THREAD;
		pre->rightChild = t;
	}
	pre = t;
	create_inthread(t->rightChild, pre);
}

BinTreeNode* first(BinTree *bt)
{
	return first(bt->root);
}
BinTreeNode* first(BinTreeNode *t)
{
	if(t == NULL)
		return NULL;
	while(t->ltag == LINK)
		t = t->leftChild;
	return t;
}

BinTreeNode* last(BinTree *bt)
{
	return last(bt->root);
}
BinTreeNode* last(BinTreeNode *t)
{
	if(t == NULL)
		return NULL;
	while(t->rtag == LINK)
		t = t->rightChild;
	return t;
}

BinTreeNode* next(BinTree *bt, BinTreeNode *cur)
{
	return next(bt->root, cur);
}
BinTreeNode* next(BinTreeNode *t, BinTreeNode *cur)
{
	if(t==NULL || cur==NULL)
		return NULL;
	if(cur->rtag == THREAD)
		return cur->rightChild;
	return first(cur->rightChild);
}
BinTreeNode* prio(BinTree *bt, BinTreeNode *cur)
{
	return prio(bt->root, cur);
}
BinTreeNode* prio(BinTreeNode *t, BinTreeNode *cur)
{
	if(t==NULL || cur==NULL)
		return NULL;
	if(cur->ltag == THREAD)
		return cur->leftChild;
	return last(cur->leftChild);
}

void inorder(BinTree *bt)
{
	inorder(bt->root);
}
void inorder(BinTreeNode *t)
{
	for(BinTreeNode *p=first(t); p!=NULL; p = next(t,p))
	{
		cout<<p->data<<" ";
	}
	cout<<endl;
}

BinTreeNode* parent(BinTree *bt, BinTreeNode *cur)
{
	return parent(bt->root, cur);
}
BinTreeNode* parent(BinTreeNode *t, BinTreeNode *cur)
{
	return NULL;
}