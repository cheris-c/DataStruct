
//无向图的创建, 利用邻接矩阵的方式存储
#include<iostream>
using namespace std;

template<class V, class E>
class CGraphMtx
{
public:
	CGraphMtx(int sz = DEFAULT_VTX_SIZE)
	{
		m_maxVtxSize = sz > DEFAULT_VTX_SIZE ? sz : DEFAULT_VTX_SIZE;

		m_vertex = new V[m_maxVtxSize];
		for (int i = 0; i < m_maxVtxSize; ++i)
		{
			m_vertex[i] = V();
		}

		m_edge = new E*[m_maxVtxSize];
		for (int i = 0; i < m_maxVtxSize; ++i)
		{
			m_edge[i] = new E[m_maxVtxSize];
		}

		for (int i = 0; i < m_maxVtxSize; ++i)
		{
			for (int j = 0; j < m_maxVtxSize; ++j)
				m_edge[i][j] = E();
		}


		m_edgeSize = m_vtxSize = 0;
	}

	~CGraphMtx()
	{
		delete m_vertex;
		delete []m_edge;
	}

public:
	bool isFull() const { return m_vtxSize >= m_maxVtxSize; }
	int numberOfVtx() const { return m_vtxSize; }
	int numberOfEdge() const { return m_edgeSize; }

	int getIdx(const V& v) const 
	{
		for (int i = 0; i < m_vtxSize; ++i)
		{
			if (m_vertex[i] == v)
				return i;
		}

		return -1;
	}

public:
	bool insertVtx(const V& v);
	bool insertEdge(const V& vfst, const V& vscd, const E& weight);

	bool removeVtx(const V& v);						//删除顶点V和它所关联的边
	bool removeEdge(const V& vfst, const V& vscd);	//删除边（vfst, vscd）

	int getFirstNeighbor(const V& v) const;				//取顶点v的第一个邻接顶点
	int getNextNeighbor(const V& v, const V& w) const;	//取顶点v的邻接顶点w的下一邻接顶点
	
	void showGraph();

private:
	static const int DEFAULT_VTX_SIZE = 10;
	V *m_vertex;
	E **m_edge;
	
	int m_maxVtxSize;
	int m_vtxSize;
	int m_edgeSize;
};

////////////////////////////////////////////////////////////////////////
template<class V, class E>
bool CGraphMtx<V, E>::insertVtx(const V& v)
{
	if (isFull()) return false;

	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (v == m_vertex[i])
			return true;
	}

	m_vertex[m_vtxSize++] = v;
	return true;
}

//插入边，weight为权值
template<class V, class E>
bool CGraphMtx<V, E>::insertEdge(const V& vfst, const V& vscd, const E& weight)
{
	int vf = getIdx(vfst);
	int vs = getIdx(vscd);

	if (vs == -1 || vf == -1 || weight == E())
		return false;

	if (m_edge[vf][vs] == E())
	{
		m_edge[vf][vs] = m_edge[vs][vf] = weight;
		m_edgeSize++;
	}

	return true;
}

template<class V, class E>
bool CGraphMtx<V, E>::removeVtx(const V &v)
{
	int vIdx = getIdx(v);
	int num = 0;   
	if (vIdx == -1) return false;

	//记录与当前顶点相关的边的数目
	for (int i = 0; i < m_vtxSize; ++i)
	{
		if (m_edge[vIdx][i] != E())
		{
			++num;
			m_edge[vIdx][i] = m_edge[i][vIdx] = E(); //删除与该顶点相关的所有边
		}
	}

	//将矩阵最后一行和最后一列前移覆盖要删除的行和列
	if (v != m_vtxSize)
	{
		for (int i = 0; i < m_vtxSize; ++i)
		{
			m_edge[vIdx][i] = m_edge[m_vtxSize-1][i];
			m_edge[i][vIdx] = m_edge[i][m_vtxSize-1];
		}

		m_vertex[vIdx] = m_vertex[m_vtxSize-1];
	}
	--m_vtxSize;
	m_edgeSize -= num;

	return true;
}

//删除边（vfst, vscd）
template<class V, class E>
bool CGraphMtx<V, E>::removeEdge(const V& vfst, const V& vscd)
{
	int vf = getIdx(vfst);
	int vs = getIdx(vscd);

	if (vf == -1 || vs == -1) return false;

	if (m_edge[vf][vs] != E())
	{
		m_edge[vf][vs] = m_edge[vs][vf] = E();
		m_edgeSize--;
	}

	return true;
}

//获取v的第一个邻接顶点
template<class V, class E>
int CGraphMtx<V, E>::getFirstNeighbor(const V& v) const
{
	int vIdx = getIdx(v);
	if (vIdx != -1)
	{
		for (int i = 0; i < m_vtxSize; ++i)
		{
			if (m_edge[vIdx][i] != E())
				return i;
		}
	}

	return -1;
}

//取顶点v的邻接顶点w的下一个v的邻接顶点
template<class V, class E>
int CGraphMtx<V, E>::getNextNeighbor(const V& v, const V& w) const
{
	int vIdx = getIdx(v);
	int wIdx = getIdx(w);

	if (wIdx != -1 && vIdx != -1)
	{
		for (int i = wIdx + 1; i < m_vtxSize; ++i)
		{
			if (m_edge[vIdx][i] != E())
				return i;
		}
	}

	return -1;	
}

template<class V, class E>
void CGraphMtx<V, E>::showGraph()
{
	cout << " ";
	for (int i = 0; i < m_vtxSize; ++i)
	{
		cout << " " << m_vertex[i];
	}
	cout << endl;

	for (int i = 0; i < m_vtxSize; ++i)
	{
		cout << m_vertex[i] << " ";
		for (int j = 0; j < m_vtxSize; ++j)
		{
			cout << m_edge[i][j] << " ";
		}
		cout << endl;
	}
}

