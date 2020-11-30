#pragma once
#include"utili.h"

typedef struct Queue
{
	ElemType *base;
	int front;
	int rear;
}Queue;
bool isfull(Queue *Q)
{
	return ((Q->rear+1)%DEFAULT_SIZE) == (Q->front);
}
bool isempty(Queue *Q)
{
	return Q->front == Q->rear;
}
void init_queue(Queue *Q)
{
	Q->base = (ElemType *)malloc(sizeof(ElemType) * DEFAULT_SIZE);
	assert(Q->base != NULL);
	Q->front = Q->rear = 0;
}
void enqueue(Queue *Q, ElemType x)
{
	if(isfull(Q))
	{
		cout<<"队已满，"<<x<<" 不能入队."<<endl;
		return;
	}
	Q->base[Q->rear] = x;
	Q->rear = (Q->rear+1) % DEFAULT_SIZE;
}
void dequeue(Queue *Q)
{
	if(isempty(Q))
	{
		cout<<"队已空，不能出队."<<endl;
		return;
	}
	Q->front = (Q->front+1) % DEFAULT_SIZE;
}

void show_queue(Queue *Q)
{
	for(int i=Q->front; i!=Q->rear; i=(i+1)%DEFAULT_SIZE)
	{
		cout<<Q->base[i]<<" ";
	}
	cout<<endl;
}



/*
//

bool isfull(Queue *Q)
{
	return Q->rear >= DEFAULT_SIZE;
}
bool isempty(Queue *Q)
{
	return Q->front == Q->rear;
}

void init_queue(Queue *Q)
{
	Q->base = (ElemType *)malloc(sizeof(ElemType) * DEFAULT_SIZE);
	assert(Q->base != NULL);
	Q->front = Q->rear = 0;
}
void enqueue(Queue *Q, ElemType x)
{
	if(isfull(Q))
	{
		cout<<"队已满，"<<x<<" 不能入队."<<endl;
		return;
	}
	Q->base[Q->rear++] = x;
}
void dequeue(Queue *Q)
{
	if(isempty(Q))
	{
		cout<<"队已空，不能出队."<<endl;
		return;
	}
	Q->front++;
}
ElemType gethead(Queue *Q)
{
	if(isempty(Q))
	{
		cout<<"队已空，不能取对头元素."<<endl;
		return;
	}
	return Q->base[Q->front];
}
void show_queue(Queue *Q)
{
	for(int i=Q->front; i<Q->rear; ++i)
	{
		cout<<Q->base[i]<<" ";
	}
	cout<<endl;
}

*/