/*
本程序用来实现对赫夫曼编码的最基本的操作
主要步骤：
 1 生成一个节点数组用来存放树的节点信息
 2 初始化
 3 从中找出权值最小和权值次小节点然后生成这两个节点的双亲节点权值最小节点是该双亲节点的左孩子次小为右孩子然后将该双亲节点加入到节点数组中并标记为已加入
 4 重复三步骤知道赫夫曼树构造成功
*/
#include<stdio.h>
#include<malloc.h>
#define LEN_CODE sizeof(HaffmanCode)
#define LEN_NODE sizeof(haffmannode)
#define MAXWEIGHT 1000 //用来存储最大的权值数
#define MaxBits 30 //用来存储转化后的编码

typedef struct HaffManTree
{
	int weight;  //存放节点的权值
	int LeftChild,RightChild,Parent;  //采用仿真指针方法存放节点的左右孩子和双亲下标
	int flag;  //用来判断该节点是否已经加入了赫夫曼树中( 0表示未加入，1表示已经加入 )
}haffmannode;

typedef struct HaffMancode
{
	int bits[MaxBits]; //用来存放编码
	int weight;  //用来存放对应的权值
	int start; //存放编码的起始位置
}HaffmanCode;

void MakeTree(int weight[],int n,haffmannode haffmantree[]);
void MakeCode(haffmannode haffmantree[],int n,HaffmanCode haffmancode[]);
void DispCode(char temp[],haffmannode tree[],HaffmanCode Code[],int n);