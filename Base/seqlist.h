#ifndef _SEQLIST_H
#define _SEQLIST_H

#include"utili.h"
///////////////////////////////////

typedef struct SeqList
{
	ElemType *base;
	size_t    capacity;
	size_t    size;
}SeqList;

///////////////////////////////////////////
BOOL isfull(SeqList *lt);
BOOL isempty(SeqList *lt);
void init_list(SeqList *lt);
void show_list(SeqList *lt);
BOOL push_back(SeqList *lt, ElemType x);
BOOL push_front(SeqList *lt, ElemType x);
BOOL pop_back(SeqList *lt);
BOOL pop_front(SeqList *lt);
BOOL insert(SeqList *lt, int pos, ElemType x);
BOOL insert(SeqList *lt, ElemType x);
BOOL erase(SeqList *lt, int pos);
BOOL erase_val(SeqList *lt, ElemType key);
int  find(SeqList *lt, ElemType key);
size_t length(SeqList *lt);
void clear(SeqList *lt);
void revserse(SeqList *lt);
void sort(SeqList *lt);
void destroy(SeqList *lt);
///////////////////////////////////////////
BOOL isfull(SeqList *lt)
{
	if(lt->size >= lt->capacity)
		return TRUE;
	return FALSE;
}
BOOL isempty(SeqList *lt)
{
	if(lt->size == 0)
		return TRUE;
	return FALSE;
}
void init_list(SeqList *lt)
{
	lt->base = (ElemType*)malloc(sizeof(ElemType)*DEFAULT_SIZE);
	assert(lt->base != NULL);
	lt->capacity = DEFAULT_SIZE;
	lt->size = 0;
}

BOOL push_back(SeqList *lt, ElemType x)
{
	if(isfull(lt))
	{
		cout<<"顺序表已满, "<<x<<" 插入失败!"<<endl;
		return FALSE;
	}
	lt->base[lt->size++] = x;
	//size++;
	return TRUE;
}
BOOL push_front(SeqList *lt, ElemType x)
{
	if(isfull(lt))
	{
		cout<<"顺序表已满, "<<x<<" 插入失败!"<<endl;
		return FALSE;
	}

	for(int i=lt->size; i>0; --i)
	{
		lt->base[i] = lt->base[i-1];
	}
	lt->base[0] = x;
	lt->size++;
	return TRUE;

}
void show_list(SeqList *lt)
{
	for(int i=0; i<lt->size; ++i)
	{
		cout<<lt->base[i]<<" ";
	}
	cout<<endl;
}

BOOL pop_back(SeqList *lt)
{
	if(isempty(lt))
	{
		cout<<"顺序表已空, pop_back 删除失败!"<<endl;
		return FALSE;
	}
	lt->size--;
	return TRUE;
}
BOOL pop_front(SeqList *lt)
{
	if(isempty(lt))
	{
		cout<<"顺序表已空, 删除失败!"<<endl;
		return FALSE;
	}
	for(int i=0; i<lt->size-1; ++i)
	{
		lt->base[i] = lt->base[i+1];
	}
	lt->size--;
	return TRUE;
}

BOOL insert(SeqList *lt, int pos, ElemType x)
{
	if(pos<0 || pos>lt->size)
	{
		cout<<"插入的位置非法,插入失败."<<endl;
		return FALSE;
	}
	if(isfull(lt))
	{
		cout<<"顺序表已满, insert 插入失败!"<<endl;
		return FALSE;
	}
	for(int i=lt->size; i>pos; --i)
	{
		lt->base[i] = lt->base[i-1];
	}
	lt->base[pos] = x;
	lt->size++;
	return TRUE;
}

BOOL insert(SeqList *lt, ElemType x)
{
	if(isfull(lt))
	{
		cout<<"顺序表已满, insert 插入失败!"<<endl;
		return FALSE;
	}
	int i;
	for(i=0; i<lt->size&&x>lt->base[i]; ++i);
	/*
	for(i=0; i<lt->size; ++i)
	{
		if(x < lt->base[i])
			break;
	}
	*/
	for(int j=lt->size; j>i; --j)
	{
		lt->base[j] = lt->base[j-1];
	}
	lt->base[i] = x;
	lt->size++;
	return TRUE;
}
BOOL erase(SeqList *lt, int pos)
{
	if(isempty(lt))
	{
		cout<<"表已空,不能删除!"<<endl;
		return FALSE;
	}
	if(pos<0 || pos>=lt->size)
	{
		cout<<"位置非法,不能删除数据!"<<endl;
		return FALSE;
	}

	for(int i=pos; i<lt->size-1; ++i)
	{
		lt->base[i] = lt->base[i+1];
	}
	lt->size--;

	return TRUE;
}

int  find(SeqList *lt, ElemType key)
{
	for(int i=0; i<lt->size; ++i)
	{
		if(lt->base[i] == key)
			return i;
	}
	return -1;
}

BOOL erase_val(SeqList *lt, ElemType key)
{
	int pos = find(lt, key);
	if(pos == -1)
	{
		cout<<"要删除的值不存在,不能删除!"<<endl;
		return FALSE;
	}
	erase(lt,pos);
}
size_t length(SeqList *lt)
{
	return lt->size;
}
void clear(SeqList *lt)
{
	lt->size = 0;
}
void revserse(SeqList *lt)
{
	if(isempty(lt) || lt->size==1)
		return;
	int low = 0;
	int high = lt->size-1;
	ElemType tmp;
	while(low < high)
	{
		tmp = lt->base[low];
		lt->base[low] = lt->base[high];
		lt->base[high] = tmp;
		low++;
		high--;
	}
}

void sort(SeqList *lt)
{
	ElemType tmp;
	for(int i=0; i<lt->size-1; ++i)
	{
		for(int j=0; j<lt->size-i-1; ++j)
		{
			if(lt->base[j] > lt->base[j+1])
			{
				tmp = lt->base[j];
				lt->base[j] = lt->base[j+1];
				lt->base[j+1] = tmp;
			}
		}
	}
}
void destroy(SeqList *lt)
{
	free(lt->base);
	lt->capacity = lt->size = 0;
}
#endif