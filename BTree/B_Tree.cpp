#include "./B_Tree.h"

template <typename T>
BTNodePosi(T) BTree<T>::search(const T &e) 
{
	BTNodePosi(T) v = _root;//从根节点开始
	_hot = NULL;

	while (v)	//逐层查找
	{
		Rank r = v->key.search(e);		//在当前节点对应的向量中顺序查找
		
		if (r >= 0 && e == v->key[r])	//查找成功，返回
			return v;

		_hot = v;
		v = v->child[r+1];   //沿引用转至对应的下层子树，并载入其根I/O
	}	//若因!v而退出，则意味着抵达外部结点，超找失败

	return NULL;
}

template <typename T> 
bool BTree<T>::insert(const T &e) {
	BTNodePosi(T) v = search(e);
	if (v)                //确认e不存在 
		return false;

	Rank r = _hot->key.search(e); 	//在节点_hot中确认插入位置

	_hot->key.insert(r + 1, e);		//将新关键码插至对应的位置		
	_hot->child.insert(r + 2, NULL);//创建一个空子树指针
	
	_size++;
	solveOverflow(_hot);  //如发生上溢，需做分裂

	return true;
}

template <typename T>
void BTree<T>::solveOverflow(BTNodePosi(T) v) 
{
	if (_order >= v->child.size())  //递归基：不再上溢
		return;

	Rank s = _order / 2;  //轴点（此时_order = key.size() = child.size() - 1）
	BTNodePosi(T) u = new BTNode<T>();

	for (Rank j = 0; j < _order - s - 1; j++) //分理处右侧节点u（效率低可改进）
	{
		u->child.insert(j, v->child.remove(s + 1)); //v右侧_order-s-1个孩子 
		u->key.insert(j, v->key.remove(s + 1));		//v右侧_order-s-1个关键码
	}

	u->child[_order - s - 1] = v->child.remove(s + 1); //移动v最右边的孩子

	//？？？为什么child[0]不为NULL，其他孩子节点都不为NULL
	if (u->child[0]) // 若u的孩子们非空，则统一令其以u为父节点
	{
		for （Rank j = 0; j < _order - s; j++）
			u->child[j]->parent = u;
	}

	BTNodePosi(T) p = v->parent; //v当前的父节点p
	if (!p)			//若p为空，则创建之（全树最高层，新根节点恰好两度）
	{
		_root = p = new BTNode<T>(); 
		p->child[0] = v;
		v->parent = p;
	}

	Rank r = 1 + p->key.search(v->key[0]); 	//p中指向u的指针的秩

	p->key.insert(r, v->key.remove(s)); 	//轴点关键码上升
	p->child.insert(r + 1, u);
	u->parent = p;		//新节点u与父节点p互联

	solveOverflow(p);   //上升一层，如果有必要则继续分裂——至多递归O(logn)层
}

template <typename T>
bool BTree<T>::remove(const T &e) 
{
	BTNodePosi(T) v = search(e);
	if (!v) 			//确认e存在
		return false;  

	Rank r = v->key.search(e); //确定e在v中的秩
	if (v->child[0])  //若v非叶子节点
	{
		BTNodePosi(T) u = v->child[r+1]; 
		//在右子树中一直向左，即可
		while(u->child[0]) 
		{
			u = u->child[0];  //找到e的后继（必属于叶节点）
		}

		//与e的后继交换位置
		v->key[r] = u->key[0];
		v = u; 
		r = 0;
	}	//至此，v必然位于最底层，且其中第r个关键码就是待删除者

	v->key.remove(r);
	v->child.remove(r+1);

	_size--;
	solveOverflow(v); //如有需要，需做旋转和合并
	
	return true;
}

template <typename T>
void BSTree<T>::solveUnderflow(BTNodePosi(T) v) //解决因删除而下溢后的合并处理
{
	if ((_order + 1) / 2 <= v->child.size()) 
		return;

	BTNodePosi(T) p = v->parent;
	if (!p)
	{
		//递归基：已到根节点
		return;
	}

	Rank r = 0;
	while (p->child[r] != v)
		r++;

	//情况一： 若v的左兄弟存在，且至少包含m/2的上整数个关键码
	if (r > 0)    //若v不是p的第一个孩子
	{
		BTNodePosi(T) ls = p->child[r - 1];  //左兄弟必存在

		if((_order + 1) / 2 < ls->child.size()) //若该节点足够“胖”
		{
			v->key.insert(0, p->key[r-1]);  //（p借出的关键码给v，最为最小关键码）
			p->key[r-1] = ls->key.remove(ls->key.size() - 1); //ls的最大关键码转入p

			//同时ls的最右侧孩子过继给v（作为v的最左侧孩子）
			v->child.insert(0, ls->child.remove(ls.child.size() - 1)); 
			
			if (v->child[0])
			{
				v->child[0]->parent = v;
			}

			return; //至此，通过右旋已完成当前层（以及所有层）的下溢处理
		}
	}

	//情况二： 若v的右兄弟存在，且至少包含m/2的上整数个关键码
	if (p->child.size() -1 > r) 
	{	
		BTNodePosi(T) rs = p->child[r + 1];  //右兄弟必存在

		if((_order + 1) / 2 < rs->child.size()) //若该节点足够“胖”,大于或等于m/2的上整
		{
			v->key.insert(v->key.size(), p->key[r]);  //p借出的关键码给v，做为最大关键码
			p->key[r-1] = rs->key.remove(0); //rs的最小关键码转入p

			//同时rs的最左侧孩子过继给v（作为v的最右侧孩子）
			v->child.insert(v->child.size(), rs->child.remove(0); 
			
			if (v->child[v->child.size()-1])
			{
				v->child[v->child[size()-1]]->parent = v;
			}

			return; //至此，通过右旋已完成当前层（以及所有层）的下溢处理
		}
	}

	//情况三: L和R或者不存在，或者所含的关键码不足m/2的上整数个。
	if (r > 0)  //与左兄弟合并
	{
		BTNodePosi(T) ls = p->child[r-1];  //左兄弟存在

		ls->key.insert(ls->key.size(), p->key.remove(r-1));
		p->child.remove(r);  //pd的第r-1个关键码转入ls，v不再是p的第r个孩子

		//v的最左孩子过继给ls做最右侧孩子
		ls->child.insert(ls->child.size(), v->child.remove(0));
		if (ls->child[ls->child.size()-1]) 
			ls->child[ls->child.size()-1]->parent = ls;

		//将v剩余的关键码和孩子，依次转入ls
		while(!v->key.empty())
		{
			ls->key.insert(ls->key.size(), v->key.remove(0));
			ls->child.insert(ls->child.size(), v->child.remove(0));

			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls
		}

		release(v);
	}
	else 		//与右兄弟合并,与上面完全对称
	{
		BTNodePosi(T) rs = p->child[r + 1];

		rs->key.insert(0, p->key.remove(r));
		p->child.remove(r)
	
		rs->child.insert(0, v->child.remove(v->child.size()-1));
		if (rs->child[0])
			rs->child[0]->parent = rs;

		while(!v->key.empty())
		{
			rs->key.insert(0, v->key.remove(v->child.size()-1));
			rs->child.insert(0, v->child.remove(v->child.size()-1));

			if (rs->child[0])
				rs->child[0]->parent = rs;
		}

		release(v);		
	}

	solveUnderflow(p); //上升一层，继续分裂（至多O(logn)层）

	return
}