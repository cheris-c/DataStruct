#include "BSTree.h"

int main()
{
	BSTree<int> bst;

	int arr[] = { 45, 12, 90, 37, 3, 53, 100, 61, 24, 78 };
	
	for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
	{
		bst.insert(arr[i]);
	}

	bst.inOrder();
	cout << endl;

	int tmp = bst.max();
	cout << tmp << endl;
	tmp = bst.min();
	cout << tmp << endl;

	BSTNode<int> *ptr = bst.find(37);
	if (ptr != NULL)
		cout << ptr->getData() << endl;
	
 	bst.remove(37);
	bst.inOrder();
	cout << endl;

	return 0;
}