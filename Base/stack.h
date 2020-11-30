
#pragma once
#include"utili.h"

typedef struct Stack
{
	ElemType *base;
	size_t    capacity;
	int       top;
}Stack;

BOOL isfull(Stack *st);
BOOL isempty(Stack *st);
void init_stack(Stack *st);
void push(Stack *st, ElemType x);
void show_stack(Stack *st);
ElemType gettop(Stack *st);
void clear(Stack *st);
void destroy_stack(Stack *st);

BOOL isfull(Stack *st)
{
	if(st->top >= st->capacity)
		return TRUE;
	return FALSE;
}
BOOL isempty(Stack *st)
{
	if(st->top == 0)
		return TRUE;
	return FALSE;
}
void init_stack(Stack *st)
{
	st->base = (ElemType*)malloc(sizeof(ElemType)*DEFAULT_SIZE);
	assert(st->base != NULL);
	st->capacity = DEFAULT_SIZE;
	st->top = 0;
}
ElemType gettop(Stack *st)
{
	if(isempty(st))
	{
		cout<<"栈已空，不能取栈顶元素."<<endl;
		return INVALID_VAL;
	}
	return st->base[st->top-1];
}
void push(Stack *st, ElemType x)
{
	if(isfull(st))
	{
		cout<<"栈已满，"<<x<<"不能入栈."<<endl;
		return;
	}
	st->base[st->top++] = x;
}
void pop(Stack *st)
{
	if(isempty(st))
	{
		cout<<"栈已空，不能出栈."<<endl;
		return;
	}
	st->top--;
}
void show_stack(Stack *st)
{
	for(int i=st->top-1; i>=0; --i)
	{
		cout<<st->base[i]<<endl;
	}
}
void clear(Stack *st)
{
	st->top = 0;
}
void destroy_stack(Stack *st)
{
	free(st->base);
	st->base = NULL;
	st->capacity = st->top = 0;
}