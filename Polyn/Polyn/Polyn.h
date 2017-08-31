#ifndef _POLYN_H
#define _POLYN_H

#include<iostream>																				  

using namespace std;	   

#define LIST_OK 0
#define LIST_ERROR -1

typedef struct PolynNode
{
	float coef; //系数
	int expn;	//项数
	struct PolynNode *link;
}PolynNode;

typedef PolynNode* Polyn;

int compare(Polyn pa, Polyn pb);
void _insert(Polyn &pn, PolynNode *s);
void InitPolyn(Polyn &pn);
void CreatePolyn(Polyn &pn, int m);
void ShowPolyn(Polyn pn);
void deletePolyn(Polyn pn);

Polyn PolynAdd(Polyn pa, Polyn pb); //加
Polyn PolynSub(Polyn pa, Polyn pb); //减
Polyn PolynMul(Polyn pa, Polyn pb); //乘

#endif