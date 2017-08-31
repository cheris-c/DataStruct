#pragma once

#include<iostream>
#include<assert.h>				
#include"Stack.h"
using namespace std;

const char OperType[] = {'+', '-', '*', '/', '(', ')', '#'};  
const int OPER_SIZE = sizeof(OperType) / sizeof(char);

bool IsOper(const char exp)	
{
	for (int i = 0; i < OPER_SIZE; ++i)
	{
		if (exp == OperType[i])
			return true;
	}
	return false;
}

int GetIndex(const char oper)
{
	for (int i = 0; i < OPER_SIZE; ++i)
	{
		if (oper == OperType[i])
			return i;
	}

	return -1;
}

char Compare(const char oper1, const char oper2)
{
	//这里定义的运算符优先级数组要与上面的操作符数组顺序对应起来，以便通过操作符在操作符数组中的下标获取运算符的优先级
	const char pri[][8] = {
			/*'+', '-',  '*', '/',  '(',  ')',  '#'*/			
   /*'+'*/  { '<', '<', '<', '<', '<', '>', '>' },
   /*'-'*/  { '<', '<', '<', '<', '<', '>', '>' },
   /*'*'*/  { '>', '>', '<', '<', '<', '>', '>' },
   /*'/'*/  { '>', '>', '<', '<', '<', '>', '>' },
   /*'('*/  { '<', '<', '<', '<', '<', '=', '0' },
   /*')'*/  { '>', '>', '>', '>', '0', '>', '>' },
   /*'#'*/  { '<', '<', '<', '<', '<', '0', '=' } };

	int i = GetIndex(oper1);
	int j = GetIndex(oper2);

	return pri[i][j];
}
																
int	Evaluate(int a, const char op, int b)
{																															  
	int opnd1 = a, opnd2 = b;
	switch (op)
	{
	case '+':
		return opnd1 + opnd2;
		break;
	case '-':
		return opnd1 - opnd2;
		break;
	case '*':
		return opnd1*opnd2;
		break;
	case '/':
		assert(opnd2 != 0);
		return opnd1 / opnd2;
		break;
	default:
		break;
	}
}

int convert(const char** c, int *n)
{
	const char *ch = *c;
	int res = 0;
	do
	{				   
		res = res * 10 + (*ch - '0');
		++ch;
		(*n)++;
	} while (isdigit(*ch));
	ungetc(*ch, stdin);

	return res;
}

int EvaluateExpression(const char* exp)
{
	Stack<char> OPND;
	Stack<char> OPER;	
	int n;
	char a, b, op; // val = a op b
	int val;
	int count = 0;
	OPER.Push('#');
	while(*exp!='#' || OPER.GetTop()!='#')
	{
		count = 0;
		if(!IsOper(*exp))
		{
			n = convert(&exp, &count);
			OPND.Push(n);
			exp += count;
		}
		else
		{
			char res = Compare(*exp, OPER.GetTop());
			switch(res)
			{
			case '>':
				OPER.Push(*exp);
				exp++;
				break;
			case '<':
				op = OPER.GetTop();
				OPER.Pop();
				b = OPND.GetTop();
				OPND.Pop();
				a = OPND.GetTop();
				OPND.Pop();
				val = Evaluate(a,op,b); //
				OPND.Push(val);
				break;
			case '=':
				OPER.Pop();
				break;
			}
		}
	}
	return OPND.GetTop();
}
