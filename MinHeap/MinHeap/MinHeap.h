//最小堆的定义
//最小堆其实类似于一个优先级队列，入从最后入，删从顶端删，而且删除的是最小元素,就类似于数据越小优先级越高
#pragma once

#include <iostream>
using namespace std;

template<class Type>
class MinHeap
{
public:
	MinHeap(int sz = DEFAULT_HEAP_SIZE)
	{
		m_capacity = sz > DEFAULT_HEAP_SIZE ? sz : DEFAULT_HEAP_SIZE;
		m_heap = new Type[m_capacity];
		if (NULL == m_heap)
		{
			cout << "Allot memory failed!" << endl;
			exit(1);
		}

		m_size = 0;
	}
	MinHeap(Type arr[], int len)
	{
		m_capacity = len > DEFAULT_HEAP_SIZE ? len : DEFAULT_HEAP_SIZE;
		m_heap = new Type[m_capacity];
		if (NULL == m_heap)
		{
			cout << "Allot memory failed!" << endl;
			exit(1);
		}

		for (int i = 0; i < len; ++i)	m_heap[i] = arr[i];
		m_size = len;

		//调整该序列为最小堆
		int pos = m_size / 2 - 1;     //从最后一个分支开始调整，记录最后一个分支的父节点的下标
		while (pos >= 0)
		{
			siftDown(pos, m_size - 1);//局部自上向下调整
			--pos;  
		}
	}

public:
	bool IsEmpty() const { return m_size == 0; }
	bool IsFull()  const { return m_size >= m_capacity; }
	int  GetSize() const { return m_size; }

	bool Insert(const Type &x);
	bool RemoveMin(Type &x);
	void ShowHeap();

private:
	void siftDown(int curIdx, int maxIdx/*最后一个节点的下标*/);
	void siftUp(int curIdx);

private:
	enum{DEFAULT_HEAP_SIZE = 10};
	Type *m_heap;
	int m_size;
	int m_capacity;
};


/////////////////////////////////////////////////////////////////////////
//最小堆向下调整算法的实现
/*将左右节点中最小的那个和父节点交换*/
template<class Type>
void MinHeap<Type>::siftDown(int curIdx, int maxIdx)
{
	int curPos = curIdx, leftIdx = 2 * curPos + 1;
	
	while (leftIdx <= maxIdx)
	{
		if (leftIdx < maxIdx && m_heap[leftIdx] > m_heap[leftIdx + 1])
			++leftIdx;

		if (m_heap[leftIdx] < m_heap[curPos])
		{
			Type tmp = m_heap[leftIdx];
			m_heap[leftIdx] = m_heap[curPos];
			m_heap[curPos] = tmp;

			curPos = leftIdx;
			leftIdx = 2 * curPos + 1;
		}
		else
			break;
	}
}

//最小堆向上调整算法
/*与父节点相比较，如果小则交换两个的值，大则不变*/
template<class Type>
void MinHeap<Type>::siftUp(int curIdx)
{
	int curPos = curIdx, pIdx = (curPos-1)/2;
	while (pIdx > 0)
	{
		if (m_heap[curPos] > m_heap[pIdx]) break;
		else
		{
			Type tmp = m_heap[pIdx];
			m_heap[pIdx] = m_heap[curPos];
			m_heap[curPos] = tmp;

			curPos = pIdx;
			pIdx = (curPos - 1) / 2;
		}
	}
}

//插入算法：每次将元素插入至堆的最后，然后向上调整堆
template<class Type>
bool MinHeap<Type>::Insert(const Type &x)
{
	if (IsFull()) { cout << "This is a full heap!" << endl; return false; }

	m_heap[m_size] = x;
	siftUp(m_size);
	++m_size;

	return true;
}

//删除算法：
/*每次删除的都是堆顶元素，即是最小的元素，然后用最后一个元素取代堆顶元素，再向下调整堆*/
template<class Type>
bool MinHeap<Type>::RemoveMin(Type &x)
{
	if (IsEmpty()){ cout << "This is an empty heap!" << endl;  return false; }
	
	x = m_heap[0];
	m_heap[0] = m_heap[m_size-1];
	--m_size;
	siftDown(0, m_size-1);
	return true;
}

//
template<class Type>
void MinHeap<Type>::ShowHeap()
{
	for (int i = 0; i < m_size; i++)
		cout << m_heap[i] << " ";
	cout << endl;
}
