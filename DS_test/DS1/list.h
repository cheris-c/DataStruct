#ifndef _LIST_H
#define _LIST_H

#include"utili.h"

//DCList
typedef struct ListNode
{
	ElemType data;
	ListNode *prev;
	ListNode *next;
}ListNode;
typedef struct List
{
	ListNode *first;
	ListNode *last;
	size_t    size;
}List;

void init_list(List *list)
{
	ListNode *s = (ListNode *)malloc(sizeof(ListNode));
	assert(s != NULL);
	list->first = list->last = s;
	list->last->next = list->first;
	list->first->prev = list->last;
	list->size = 0;
}
void push_back(List *list, ElemType x)
{
	ListNode *s = (ListNode *)malloc(sizeof(ListNode));
	assert(s != NULL);
	s->data = x;

	list->last->next = s;
	s->prev = list->last;
	list->last = s;
	list->last->next = list->first;
	list->first->prev = list->last;
	list->size++;
}
void insert(List *list, ElemType x)
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	assert(p != NULL);
	p->data = x;
	ListNode *q = list->first->next;
	while(q!=list->first && q->data<x)
		q = q->next;

	q->prev->next = p;
	p->prev = q->prev;
	p->next = q;
	q->prev = p;

	if(q == list->first)
		list->last = p;
	
	list->size++;
}
void show_list(List *list)
{
	ListNode *p = list->first->next;
	while(p != list->first)
	{
		cout<<p->data<<"-->";
		p = p->next;
	}
	cout<<"Over."<<endl;
}

BOOL erase_val(List *list, ElemType key)
{
	ListNode *p = list->first->next;
	while(p!=list->first && p->data!=key)
		p = p->next;
	if(p == list->first)
		return FALSE;

	if(p == list->last)
		list->last = p->prev;

	p->next->prev = p->prev;
	p->prev->next = p->next;
	
	free(p);
	list->size--;
}
/*
//SCList
typedef struct ListNode
{
	ElemType data;
	struct ListNode *next;
}ListNode;
typedef struct List
{
	ListNode *first;
	ListNode *last;
	size_t    size;
}List;

void init_list(List *list)
{
	ListNode *s = (ListNode *)malloc(sizeof(ListNode));
	assert(s != NULL);
	
	list->first = list->last = s;
	list->last->next = list->first;
	list->size = 0;
}

void push_back(List *list, ElemType x)
{
	ListNode *s = (ListNode *)malloc(sizeof(ListNode));
	assert(s != NULL);
	s->data = x;
	list->last->next = s;
	list->last = s;
	list->last->next = list->first;
	list->size++;
}
void show_list(List *list)
{
	ListNode *p = list->first->next;
	while(p != list->first)
	{
		cout<<p->data<<"-->";
		p = p->next;
	}
	cout<<"Over."<<endl;
}

////////////////////////////////////////////////////////
/*
//SList
typedef struct ListNode
{
	ElemType data;
	struct ListNode *next;
}ListNode;
typedef struct List
{
	ListNode *first;
	ListNode *last;
	size_t    size;
}List;
////////////////////////////////////////////
void init_list(List *list);
void push_back(List *list, ElemType x);
void push_front(List *list, ElemType x);
void pop_back(List *list);
void pop_front(List *list);
ListNode* find(List *list, ElemType key);
void show_list(List *list);
size_t length(List *list);
BOOL erase_val(List *list, ElemType key);
void insert(List *list, ElemType x);
void _insert(List *list, ListNode *s);
void clear(List *list);
void sort(List *list);
void revserse(List *list);

void _insert(List *list, ListNode *s)
{
	ListNode *p = list->first;
	while(p->next!=NULL && p->next->data<s->data)
		p = p->next;
	if(p->next == NULL)
	{
		list->last->next = s;
		list->last = s;
	}
	else
	{
		s->next = p->next;
		p->next = s;
	}
}

void init_list(List *list)
{
	ListNode *s = (ListNode*)malloc(sizeof(ListNode));
	assert(s != NULL);
	list->first = list->last = s;
	list->size = 0;
	list->last->next = NULL;
}
void push_back(List *list, ElemType x)
{
	ListNode *s = (ListNode*)malloc(sizeof(ListNode));
	assert(s != NULL);
	s->data = x;
	s->next = NULL;

	list->last->next = s;
	list->last = s;
	list->size++;
}

void push_front(List *list, ElemType x)
{
	ListNode *s = (ListNode *)malloc(sizeof(ListNode));
	assert(s != NULL);
	s->data = x;

	s->next = list->first->next;
	list->first->next = s;
	if(list->first == list->last)
		list->last = s;
	list->size++;
}

void pop_back(List *list)
{
	if(list->size == 0)
		return;
	ListNode *p = list->first;
	while(p->next != list->last)
	{
		p = p->next;
	}
	ListNode *q = p->next;
	list->last = p;
	list->last->next = NULL;
	free(q);
	list->size--;
}

void pop_front(List *list)
{
	if(list->size == 0)
		return;
	ListNode *p = list->first->next;
	list->first->next = p->next;
	free(p);
	if(list->size == 1)
		list->last = list->first;
	list->size--;
}

ListNode* find(List *list, ElemType key)
{
	ListNode *p = list->first->next;
	while(p!=list->last->next && p->data!=key)
		p = p->next;
	return p;
}

void show_list(List *list)
{
	ListNode *p = list->first->next;
	while(p != NULL)
	{
		cout<<p->data<<"-->";
		p = p->next;
	}
	cout<<"Over."<<endl;
}
size_t length(List *list)
{
	return list->size;
}

BOOL erase_val(List *list, ElemType key)
{
	ListNode *p = find(list, key);
	if(p == NULL)
		return FALSE;
	ListNode *t = list->first;
	while(t->next != p)
		t = t->next;

	if(p == list->last)
		list->last = t;
	t->next = p->next;
	free(p);
	list->size--;
	return TRUE;
}
void insert(List *list, ElemType x)
{
	ListNode *s = (ListNode*)malloc(sizeof(ListNode));
	assert(s != NULL);
	s->data = x;
	s->next = NULL;

	ListNode *p = list->first;
	while(p->next!=NULL &&  p->next->data<x)
		p = p->next;
	if(p->next == NULL) //push_back
	{
		list->last->next = s;
		list->last = s;
	}
	else
	{
		s->next = p->next;
		p->next = s;
	}
	list->size++;
}
void clear(List *list)
{
	ListNode *p = list->first->next;
	while(p != NULL)
	{
		list->first->next = p->next;
		free(p);
		p = list->first->next;
	}
	list->last = list->first;
	list->size = 0;
}

void sort(List *list)
{
	ListNode *p = list->first->next;
	ListNode *t = p->next;
	list->last = p;
	list->last->next = NULL;

	while(t != NULL)
	{
		p = t;
		t = t->next;
		p->next = NULL;
		_insert(list, p);
	}
}
void revserse(List *list)
{
	//
}
*/
#endif