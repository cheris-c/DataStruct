//²âÊÔÎÄ¼ş
#include "MinHeap.h"

int main()
{
	int arr[] = { 18, 16, 90, 32, 23, 44, 58, 199 };
	int len = sizeof(arr) / sizeof(int);
	MinHeap<int> mh(arr, len);
	mh.ShowHeap();

	mh.Insert(55);
	int x;
	for (int i = 0; i < len+1; ++i)
	{
		mh.RemoveMin(x);
		cout << x <<" ";
	}

	return 0;
}