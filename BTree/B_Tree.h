#ifndef _B_TREE_
#define _B_TREE_

#include <iostream>
#include <vector>

using namespace std;

#define BTNodePosi(T) BTNode<T>*

template <typename T> struct BTNode
{
	BTNodePosi(T) parent;		//父节点
	vector<T> key;				//数值向量（关键码）
	vector<BTNodePosi(T)> child;//孩子向量(其长度总比key多一)

	BTNode() { parent = NULL; child.insert(0, NULL); }
	BTNode(T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL) 
	{
		parent = NULL;		//根节点，初始化时，父节点为空
		key.insert(0, e);	//插入一个关键码
		
		//两个孩子
		child.insert(0, lc); 
		child.insert(1, rc);  
		
		if (lc) { lc->parent = this; }
		if (rc) { rc->parent = this; }
	}
};

template <typename T> class BTree 
{
protected:
	int _size; 				//关键码总数
	int _order; 			//阶次
	BTNodePosi(T) _root;	//根节点
	BTNodePosi(T) _hot; 	//search()最后访问的非空节点位置

	void solveOverflow(BTNodePosi(T));	//解决因插入而上溢后的分裂处理
	void solveUnderflow(BTNodePosi(T)); //解决因删除而下溢后的合并处理

public:
	BTNodePosi(T) search(const T &e);	//查找
	bool insert(const T &e);			//插入
	bool remove(const T &e);			//删除
};

#endif //_B_TREE_
