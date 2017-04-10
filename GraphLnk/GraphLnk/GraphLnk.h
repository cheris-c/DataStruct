#pragma once

//无向图的创建 存储方式：邻接表
#include <iostream>
using namespace std;


template<class V, class E> class CGraphLnk;
const int DEFAULT_VTX_SIZE = 10;

////////////////////////////////////////////////////////////////////////////////////
//the declaration of edge
template<class V, class E>
class Edge
{
	friend class CGraphLnk<V, E>;

public:
	Edge(int num, E wt): dest(num), weight(wt), pNext(NULL) {}

private:
	int dest;
	E weight;
	Edge<V, E> *pNext;
};

//////////////////////////////////////////////////////////////////////////
//the declaration of vertex
template<class V, class E>
class Vertex
{
	friend class CGraphLnk<V, E>;

public:
	Vertex() : data(V()), adj(NULL) {}
	Vertex(const V& d) : data(d), adj(NULL) {}

	Vertex& operator=(const Vertex& v)
	{
		if (this != &v)
		{
			this->data = v.data;
			this->adj = v.adj;
		}

		return *this;
	}

private:
	V data;
	Edge<V, E> *adj;  //该顶点的第一个邻接顶点
};

/////////////////////////////////////////////////////////////////////////
//the declaration of CGraphLnk
template<class V, class E>
class CGraphLnk
{
public:
	CGraphLnk(int sz = DEFAULT_VTX_SIZE)
	{
		m_maxVtxSize = sz > DEFAULT_VTX_SIZE ? sz : DEFAULT_VTX_SIZE;
		m_edgeSize = m_vtxSize = 0;
		m_vtxTable = new Vertex<V, E>[m_maxVtxSize];
	}
	~CGraphLnk()
	{
		Edge<V, E> *e = NULL;
		for (int i = 0; i < m_vtxSize; ++i)
		{
			while((e = m_vtxTable[i].adj) != NULL)
			{
				m_vtxTable[i].adj = e->pNext;
				delete e;
			}
			e = NULL;
		}

		delete[]m_vtxTable;
	}

public:
	bool insertVtx(const V& v);
	bool insertEdge(const V& vfst, const V& vscd, const E& weight);
	bool removeVtx(const V& v);
	bool removeEdge(const V& vfst, const V& vscd);

	void showGraph();

public:
	int getIdx(const V& v) const;
	V getElement(const int index) const	{ return (index >= 0 && index < m_vtxSize) ? m_vtxTable[index].data : V(); }
	int	getFirstNeighbor(const V& v) const
	{
		int vIdx = getIdx(v);
		if (vIdx != -1)
		{
			Edge<V, E> *e = m_vtxTable[vIdx].adj;
			return e->dest;
		}

		return -1;
	}

	//查找v的邻接顶点w开始的下一个v的领接顶点
	int getNextNeighbor(const V& v, const V& w) const
	{
		int vIdx = getIdx(v);
		int wIdx = getIdx(w);
		if (vIdx != -1)
		{
			Edge<V, E> *e = m_vtxTable[vIdx].adj;
			while (e != NULL && e->dest != wIdx) //寻找邻接顶点w的位置
				e = e->pNext;

			if (e != NULL && e->pNext != NULL)	//通过其位置判断是否有下一个邻接顶点
				return e->pNext->dest;
		}

		return -1;
	}

	int numberOfVertex() const { return m_vtxSize; }
	int numberOfEdge() const { return m_edgeSize; }

private:
	Vertex<V, E> *m_vtxTable;
	int m_maxVtxSize;
	int m_edgeSize;
	int m_vtxSize;
};

////////////////////////////////////////////////////////////////////////////////////
//the definitions of functions declared in CGraphLnk
template<class V, class E>
bool CGraphLnk<V, E>::insertVtx(const V& v)
{
	if (m_vtxSize >= m_maxVtxSize) return false;

	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (m_vtxTable[i].data == v)
			return true;
	}

	m_vtxTable[m_vtxSize].data = v;
	m_vtxTable[m_vtxSize].adj = NULL;
	++m_vtxSize;
	return true;
}

template<class V, class E>
int CGraphLnk<V, E>::getIdx(const V& v) const
{
	Vertex<V, E> *p = m_vtxTable;
	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (m_vtxTable[i].data == v)
			return i;
	}
	return -1;
}

template<class V, class E>
bool CGraphLnk<V, E>::insertEdge(const V& vfst, const V& vscd, const E& weight)
{
	int vf = getIdx(vfst);
	int vs = getIdx(vscd);

	if (vf == -1 || vs == -1)
		return false;
	
	Edge<V, E> *tmp = m_vtxTable[vf].adj;
	while (tmp != NULL && tmp->dest != vs)
		tmp = tmp->pNext;

	if (tmp != NULL) return true;			//已经存在返回true，但是边的条数不加

	//节点插入选择前插的方式
	Edge<V, E> *newEdge = new Edge<V, E>(vs, weight);
	newEdge->pNext = m_vtxTable[vf].adj;
	m_vtxTable[vf].adj = newEdge;

	tmp = new Edge<V, E>(vf, weight);
	tmp->pNext = m_vtxTable[vs].adj;
	m_vtxTable[vs].adj = tmp;

	++m_edgeSize;

	return true;
}

/*
删除一个顶点：
思想：
	先删除与该节点相关的所有边，再去除该节点。
实现细节：
	查找邻接表找到该节点，然后查找该节点后面的链表是否为空，不为空则查找链表，找到与该节点对应的第一条边，
然后将该边删除的同时将该边中另一个节点中与该边对应的边删除，如此重复操作，直至与所删除的节点有关的所有边删除
为止。此时将最后一个节点及所对应的边移至所要删除节点的位置。
*/
template<class V, class E>
bool CGraphLnk<V, E>::removeVtx(const V& v)
{
	int vIdx = getIdx(v);
	Edge<V, E> *q = NULL,*p = NULL, *tmp = NULL;

	if (vIdx == -1) return false;

	while ((p = m_vtxTable[vIdx].adj) != NULL)
	{	
		m_vtxTable[vIdx].adj = p->pNext;
		int eIdx = p->dest;

		tmp = q = m_vtxTable[eIdx].adj;
		delete p;
		p = NULL;

		//删除与该节点邻接节点中对应的边
		while (q != NULL )		
		{
			//找到对应边
			if (q->dest == vIdx)
			{
				//同tmp的值判断该边所在位置，因为所在位置不同，删除后的连接方式不同
				if (tmp == q)
					m_vtxTable[eIdx].adj = q->pNext;
				else
					tmp->pNext = q->pNext;
				
				delete q;
				q = NULL;
				--m_edgeSize;
			}
			else  //未找到对应边
			{
				tmp = q;
				q = q->pNext;
			}
		}//while	
	}//while

	m_vtxTable[vIdx] = m_vtxTable[--m_vtxSize];
	//相互交换之后，我们需要调整一下原来与最后一个节点相连的边中另一个节点的下标
	m_vtxTable[m_vtxSize].data = V();
	m_vtxTable[m_vtxSize].adj = NULL;

	p = m_vtxTable[vIdx].adj;
	while (p != NULL)
	{
		tmp = m_vtxTable[p->dest].adj;
		while (tmp != NULL)
		{
			if (tmp->dest = m_vtxSize)
			{
				tmp->dest = vIdx;
				break;
			}
			tmp = tmp->pNext;
		}

		p = p->pNext;
	}

	return true;
}

template<class V, class E>
bool CGraphLnk<V, E>::removeEdge(const V& vfst, const V& vscd)
{
	int vf = getIdx(vfst); 
	int vs = getIdx(vscd);
	Edge<V, E> *e = NULL, *p = NULL;

	if (vf == -1 || vs == -1)	return false;
	
	//在vfst对应链表中查找被删边
	e = p = m_vtxTable[vf].adj;
	while (e != NULL && e->dest != vs)
	{
		p = e;
		e = e->pNext;
	}

	//该顶点存在相关联的边
	if (e != NULL)
	{
		if (e == p)	 //找到的节点是链表的首节点
			m_vtxTable[vf].adj = e->pNext;
		else		 //不是首节点
			p->pNext = e->pNext;

		delete e;	e = NULL;
	}
	else
		return false;

	//在vscd对应链表中查找与上面相对应的边
	p = e = m_vtxTable[vs].adj;
	while (e->dest != vf)
	{
		p = e;
		e = e->pNext;
	}

	if (e == p)
		m_vtxTable[vs].adj = e->pNext;
	else
		p->pNext = e->pNext;

	delete e;	e = NULL;
	--m_edgeSize;

	return true;
}

template<class V, class E>
void CGraphLnk<V, E>::showGraph()
{
	for (int i = 0; i < m_vtxSize; ++i)
	{
		cout << m_vtxTable[i].data << "-->";
		Edge<V, E> *e = m_vtxTable[i].adj;
		while (e != NULL)
		{
			cout << e->dest << "-->";
			e = e->pNext;
		}
		cout << "Nul." << endl;
	}
}