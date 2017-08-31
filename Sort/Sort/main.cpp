#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<time.h>
#include"Sort.h"

void timeInSort(DataType *data, int len, void(*camp)(DataType* , int))
{
	time_t start, end;
	double dif;

	time(&start);   //起始时间
	camp(data, len);   //实际运行排序函数
	time(&end);            //结束时间
	dif = difftime(end, start);    //计算耗时
	printf(" %.2f 秒\n", dif);    //输出显示实际耗时
	for (int i = 0; i < len; i++)
		printf("%d  ", data[i]);
	printf("\n");
}

int main()
{
	int i, n;
	int flag = 1;
	DataType *test1, *test2, *test3, *test4, *test5, *test6, *test7, *test8;
	time_t start, end;
	double dif;

	while (flag)
	{
		printf("please enter n ^_^ :  ");
		scanf("%d", &n);
		getchar();

		test1 = (DataType*)malloc(sizeof(DataType)*n);
		test2 = (DataType*)malloc(sizeof(DataType)*n);
		test3 = (DataType*)malloc(sizeof(DataType)*n);
		test4 = (DataType*)malloc(sizeof(DataType)*n);
		test5 = (DataType*)malloc(sizeof(DataType)*n);
		test6 = (DataType*)malloc(sizeof(DataType)*n);
		test7 = (DataType*)malloc(sizeof(DataType)*n);
		test8 = (DataType*)malloc(sizeof(DataType)*n);
		for (i = 0; i < n; i++)
		{
			test1[i].key = rand();    //随机生成测试数据
			printf("%5d\n", test1[i].key);
			test2[i].key = test1[i].key;
			printf("%5d\n", test2[i].key);
			test3[i].key = test1[i].key;
			test4[i].key = test1[i].key;
			test5[i].key = test1[i].key;
			test6[i].key = test1[i].key;
			test7[i].key = test1[i].key;
			test8[i].key = test1[i].key;
		}

		int dk[] = { 5, 3, 1 };
		time(&start);
		shellSort(test8, n, dk, 3);	//注意high为n-1
		time(&end);
		dif = difftime(end, start);
		printf("希尔排序：  %.2f 秒\n", dif);
		for (int i = 0; i < n; i++)
			printf("%d  ", test8[i]);
		printf("\n");

		printf("插入排序： ");
		timeInSort(test1, n, insertSort);
		printf("冒泡排序： ");
		timeInSort(test2, n, bubbleSort);
		printf("选择排序： ");
		timeInSort(test3, n, selectSort);
		printf("堆排序： ");
		timeInSort(test5, n, heapSort);
		printf("二路归并排序：");
		timeInSort(test6, n, mergeSort);

		time(&start);
		quickSort(test4, 0, n - 1);	//注意high为n-1
		time(&end);
		dif = difftime(end, start);
		printf("快速排序：  %.2f 秒\n", dif);
		for (int i = 0; i < n; i++)
			printf("%d  ", test4[i]);
		printf("\n");

		time(&start);
		radixSort(test7, 0, n - 1, 4);	//注意high为n-1
		time(&end);
		dif = difftime(end, start);
		printf("基数排序：  %.2f 秒\n", dif);
		for (int i = 0; i < n; i++)
			printf("%d  ", test7[i]);
		printf("\n");
	
		system("color f5");
		system("pause");
	}

	return 0;
}