# include <stdio.h>
/*
利用递归实现二分查找法
*/

int BSearch(int a[], int x, int low, int high)
//low和high均为数组下标
{
	int mid;      

	if(low > high)
		return -1;

	mid = (low+high)/2;
	if (x == a[mid])
		return mid;
	else if (x < a[mid])
		return BSearch(a, x, low, mid-1);	//前半区查找
	else
		return BSearch(a, x, mid+1, high);  //后半区查找

}

/*非递归实现二分查找*/
int bin_search(int *a, int n, int x)
{
	int head = -1, tail = n, mid = -1;
	int pos = -1;

	while (head+1 != tail)
	{
		mid = (tail+head) / 2;

		if (x > a[mid])
			head = mid;
		else
			tail = mid;
	}

	pos = tail;
	if (pos >= n || a[pos] != x)
		pos = -1;

	return pos;
}

int main()
{
	int a[] = {1, 3, 4, 5, 17, 18, 31, 33};
	int x = 17;
	int bn;

	bn = BSearch(a, x, 0, 7);
	if (-1 == bn)
		printf("x不存在于数组a中\n");
	else
		printf("x在数组a中的下标为%d\n", bn);

	return 0;
}