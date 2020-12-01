#include <stdlib.h>
#include"haffman.h"

#define MAX 255

void main()
{
	int i,flag=1,n=0;
	int *weight;
	char *temp=(char*)malloc(sizeof(char)*MAX); //用来存放用户输入的字符

	while(flag)
	{
		printf("\n请输入字符: ");
		n=0,i=0;
		while(1)
		{
			scanf("%c",&temp[i]);
			i++,n++;
			if(getchar() == '\n') { break; }
		}

		if (n==0 || n==1)
		{
			printf("此树为空或此树只有一个节点！\n");
			exit(0);
		}

		weight=(int*)malloc(sizeof(int)*n);
		printf("\n请输入%d个字符权值: ",n);
		for(i=0;i<n;i++)
		{
			scanf("%d",&weight[i]);
			getchar();
		}
		
		system("cls");
		haffmannode *tree=(haffmannode *)malloc((2*n-1)*LEN_NODE);  //构造赫夫曼树的总节点数
		HaffmanCode *code=(HaffmanCode *)malloc(LEN_CODE * n); //构造对应的编码数组

		MakeTree(weight,n,tree); //生成赫夫曼树

		MakeCode(tree,n,code); //生成对应的编码数组

		DispCode(temp,tree,code,n);  //输出赫夫曼编码

		printf("\n");
		printf("退出请按(E),其他键继续: ");
		char c = getchar();
		getchar();
		if (c== 'E' || c == 'e')
		{
			flag = 0;
		}
	}
}