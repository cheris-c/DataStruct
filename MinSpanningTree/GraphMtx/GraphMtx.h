
//无向图的创建, 利用邻接矩阵的方式存储
#include<iostream>
using namespace std;
#include <assert.h>

#define MAX_COST 0x7FFF		//假定权值为整型

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
			{
				if (i != j)
					m_edge[i][j] = MAX_COST;//初始化时用最大值初始化，表示两顶点之间没有边
				else
					m_edge[i][j] = E();
			}
		}

		m_edgeSize = m_vtxSize = 0;
	}

	~CGraphMtx()
	{
		delete m_vertex;
		delete[]m_edge;
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

public:
	//最小生成树的普理姆算法实现函数声明
	bool MST_Prime(const V& vBegin);
	E& getWeight(int v1, int v2) { return m_edge[v1][v2];}

	bool MST_Kruskal();
	static int compare(const void *a, const void *b);

private:
	static const int DEFAULT_VTX_SIZE = 10;
	V *m_vertex;
	E **m_edge;
	
	int m_maxVtxSize;
	int m_vtxSize;
	int m_edgeSize;
};

///////////////////////////////////////////////////////////////////////

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

	if (vs == -1 || vf == -1 || weight == MAX_COST)
		return false;

	if (m_edge[vf][vs] == MAX_COST)
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
			m_edge[vIdx][i] = m_edge[i][vIdx] = MAX_COST; //删除与该顶点相关的所有边
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

	if (m_edge[vf][vs] != MAX_COST)
	{
		m_edge[vf][vs] = m_edge[vs][vf] = MAX_COST;
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
			if (m_edge[vIdx][i] != MAX_COST)
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
		cout << "  " << m_vertex[i];
	}
	cout << endl;

	for (int i = 0; i < m_vtxSize; ++i)
	{
		cout << m_vertex[i] << "  ";
		for (int j = 0; j < m_vtxSize; ++j)
		{
			if (m_edge[i][j] == MAX_COST)
				cout << '#' << "  ";
			else
			cout << m_edge[i][j] << "  ";
		}
		cout << endl;
	}
	cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
/*
Prime算法描述：
两个数据结构：
		大小均同节点个数一样大
		lowCost[i]:表示以i为终点的边的最小权值,当lowCost[i]=0说明以i为终点的边的最小权值=0,也就是表示i点加入了MST
		mst[i]:表示对应lowcost[i]的起点，即说明边<mst[i],i>是MST的一条边，当mst[i]=0表示起点的下标为0而终点
	的下标为i。
		首先我们选定一个开始节点，初始化lowCost[i]为开始节点到其他各个节点的边的权值，如果不存在边则初始化为无穷大（MAX_COST）,
	图不存在自环，所以我们将自环设为0。
		然后我们a.在lowCost中找到与当前开始节点间权值最小的边，b.令该边所对应的另一节点作为开始节点，更新lowCost和mst[i],
	更新的时候必须是比当前权值小的时候才更新,否则不能保证是最小。重复执行上述步骤a、b，共执行n-1次(n为顶点个数)，因为有n个节点，
	它的最小生成树肯定有n-1条边。
*/
template<class V, class E>
bool CGraphMtx<V, E>::MST_Prime(const V &vBegin/*开始节点*/)
{
	int n = numberOfVtx();
	E *lowCost = new E[n];
	int *mst = new int[n];												  

	if (lowCost == NULL || mst == NULL) return false;

	int vf = getIdx(vBegin);
	for (int i = 0; i < n; ++i)
	{
		if (i != vf)
		{
			lowCost[i] = getWeight(vf, i);
			mst[i] = vf;
		}
		else
			lowCost[i] = 0;
	}

	int low = MAX_COST;  //从vf到其各个邻接节点的最小花费（即权值）
	int lowIdx = -1;	 //与该最小花费对应的节点的下标
	for (int i = 0; i < n - 1; ++i)
	{
		low = MAX_COST;
		lowIdx = -1;
		for (int j = 0; j < n; ++j)
		{
			if (low > lowCost[j] && lowCost[j] != 0)
			{
				low = lowCost[j];
				lowIdx = j;
			}
		}  //for j

		int begin = mst[lowIdx];
		int end = lowIdx;
		cout << m_vertex[begin] << "--->" << m_vertex[end] << ":" << m_edge[begin][end] << endl;
		lowCost[end] = 0;

		for (int i = 0; i < n; ++i)
		{
			int weight = getWeight(end, i);
			if (weight < lowCost[i])
			{
				lowCost[i] = weight;
				mst[i] = end;
			}
		}
	} //for i

	return true;
}


/*
kruskal(克鲁斯卡尔)算法：
	我们添加辅助结构类Edge，记录当前边的起点，终点和权值，然后建立边结构数组记录当前图中所有边的信息，
然后给所有边按权值排序，方便建立最小生成树。建立最小生成树时，我们从最小的边开始取，每次取出来的时候需要判断
该边的前后节点是否属于同一分量，如果属于同一分量，连接就会生成回路，所以，我们就忽略该该边，取下一条边，如果
不在同一连通分量，则利用mark_Same函数将其连接起来，使其处于同一连通分量，注意我们在这所说的连通是通过
father数组实现的，即修改father[i]改编i在该连通分量中的的上一个邻接顶点，就这样直至我们取出最后一条最后一条
边，此时得到的连通分量就是该图的最小生成树。
*/

template<class E>
class Edge
{
	template<class V> friend  ostream& operator<<(ostream& os, Edge<V> &e);
public:
	static int compare(const void *a, const void *b);
	bool is_Same(int *ft);
	void mark_Same(int *ft);

public:
	int x;	//start
	int y;	//end
	E cost;
};

//判断边权值的大小，方便排序
template<class E>
int Edge<E>::compare(const void *a, const void *b)
{
	return (*(Edge<E>*)a).cost - (*(Edge<E>*)b).cost;
}

//判断当前节点和即将与它相连的节点是否属于同一连通分量
template <class E>
bool Edge<E>::is_Same(int *ft)
{
	int i = this->x; 
	int j = this->y;

	while (ft[i] != i)
		i = ft[i];
	while (ft[j] != j)
		j = ft[j];

	return i == j;
}

//连接当前顶点，使其和它相连的节点处于同一连通分量
template <class E>
void Edge<E>::mark_Same(int *ft)
{
	int i = this->x;
	int j = this->y;				                                                   

	while (ft[i] != i)
		i = ft[i];
	while (ft[j] != j)
		j = ft[j];

 	ft[j] = i;
}

template<class V, class E>
bool CGraphMtx<V, E>::MST_Kruskal()
{
	int n = numberOfVtx();
	int size = n*(n - 1) / 2;

	Edge<E> *edge = (Edge<E> *)malloc(sizeof(Edge<E>)*size);
	if (edge == NULL)	return false;

	//记录所有边的信息
	int k = 0; 
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			if (m_edge[i][j] != 0 && m_edge[i][j] != MAX_COST)
			{
				edge[k].x = i;
				edge[k].y = j;
				edge[k].cost = m_edge[i][j];
				k++;
			}
		}	 //for i
	} //for i

	//按照从小到大排序
 	qsort(edge,k, sizeof(Edge<E>), Edge<E>::compare);

	int *father = new int[n];
	if (father == NULL) return false;

	for (int i = 0; i < n; ++i)
		father[i] = i;     //初始时每个顶点都是独立的，父节点都是自身

	int vbegin, vend;
	for (int i = 0; i < size; ++i)
	{
		if (!edge[i].is_Same(father))
		{
			vbegin = edge[i].x;
			vend = edge[i].y;
			cout << m_vertex[vbegin] << "-->" << m_vertex[vend] << " : " << edge[i] << endl;
			edge[i].mark_Same(father);
		}
	}

	return true;
}

template<class E>
ostream& operator<<(ostream& os, Edge<E> &e)
{
	cout << e.cost << " ";
	return os;
}
