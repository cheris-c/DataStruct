#include <iostream>
using namespace std;

template <class V>
class BSTree;

template <class E>
class BSTNode
{	
	friend  class BSTree<E>;

public:
	BSTNode(E d = E()):data(d), leftChild(NULL), rightChild(NULL) {}

	E getData() { return data; }
	void setData(E d) { data = d; }

private:
	E data;
	BSTNode<E>  *leftChild, *rightChild;
};


template <class V>
class BSTree
{
public:
	BSTree() : root(NULL) {}

public:
	bool insert(const V &x)	{ return insert(root, x); }
	BSTNode<V>*	find(const V &x) { return find(root, x); }
	bool remove(const V &key){ return remove(root, key); }

	void inOrder(){ return inOrder(root); }
	V max() { return max(root); }
	V min() { return min(root); }

private:
	bool insert(BSTNode<V> *&rt, const V &x);
	BSTNode<V>*	find(BSTNode<V> *rt, const V &x);
	bool remove(BSTNode<V> *&rt, const V &key);

	void inOrder(BSTNode<V> *rt);
	V max(BSTNode<V> *rt);
	V min(BSTNode<V> *rt);

private:
	BSTNode<V> *root;
};


//////////////////////////////////////////////////////////////////////////////
template <class V>
bool BSTree<V>::insert(BSTNode<V> *&rt, const V &x)
{
	if (rt == NULL)
	{
		rt = new BSTNode<V>(x);
		if (rt == NULL)
			return false;
	}
	else if (rt->data > x)
	{
		insert(rt->leftChild, x);
	}
	else
	{
		insert(rt->rightChild, x);
	}

	return true;
}

template <class V>
BSTNode<V>*	BSTree<V>::find(BSTNode<V> *rt, const V &x)
{
	if (rt == NULL)
		return NULL;
	else if (rt->data > x)
		find(rt->leftChild, x);
	else if (rt->data < x)
		find(rt->rightChild, x);
	else
		return rt;
}

template <class V>
V BSTree<V>::max(BSTNode<V> *rt)
{
	if (rt != NULL)
	{
		while (rt->rightChild != NULL)
			rt = rt->rightChild;

		return rt->data;
	}

	return V();
}

template <class V>
V BSTree<V>::min(BSTNode<V> *rt)
{
	if (rt != NULL)
	{
		while (rt->leftChild != NULL)
			rt = rt->leftChild;

		return rt->data;
	}

	return V();
}


/*左子树为空，右子女填补；右子树为空，左子女填补；左右子树均不为空，在右子树中序查找第一个子女填补*/
template <class V>
bool BSTree<V>::remove(BSTNode<V> *&rt, const V &key)
{
	if (NULL == rt)
		return false;

	if (key > rt->data)
		return remove(rt->rightChild, key);	 
	else if (key < rt->data)
		return remove(rt->leftChild, key);
	else
	{
		BSTNode<V> *p = NULL;
		if (rt->leftChild != NULL && rt->rightChild != NULL)
		{
			p = rt->rightChild;
			while (p->leftChild != NULL)
				p = p->leftChild;

			rt->data = p->data;
			remove(p, p->data);
		}
		else
		{
			p = rt;
			if (rt->leftChild == NULL)
				rt = rt->rightChild;
			else
				rt = rt->leftChild;

			delete p;
			p = NULL;
		}
	} //else
	return true;
}

template <class V>
void BSTree<V>::inOrder(BSTNode<V> *rt)
{
	if (rt != NULL)
	{
		inOrder(rt->leftChild);
		cout << rt->data << " ";
		inOrder(rt->rightChild);		
	}
}

