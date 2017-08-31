#include "Polyn.h"
#include "assert.h"				

void InitPolyn(Polyn &pn)
{
	pn = NULL;
}

void _insert(Polyn &pn, PolynNode *s)
{
	if (s->coef == 0)
	{
		free(s);
		s = NULL;
	}
	else
	{
		if (NULL == pn)
		{
			pn = s;
			return;
		}
		PolynNode *p = pn;
		PolynNode *q = NULL;
		while (p != NULL && p->expn > s->expn)
		{
			q = p;
			p = p->link;
		}

		//p == NULL时，则s为尾插，当p不为NULL时，要注意两项的指数是否相等，还要注意头插的情况（q==NULL）
		if (p == NULL)
			q->link = s;
		else if (p != NULL && s->expn > p->expn)
		{
			if (q == NULL)
			{
				s->link = p;
				pn = s;
			}
			else
			{
				q->link = s;
				s->link = p;
			}
		}
		else if (s->expn == p->expn && p!= NULL)
		{
			p->coef += s->coef;
			
			if (p->coef == 0)
			{													  
				q->link = p->link;		//释放前要将该节点前后连接起来
				free(p);
				p = NULL;
			}
			free(s);
			s = NULL;
		}
	}
	
}	
	  
void CreatePolyn(Polyn &pn, int m)
{
	for (int i = 1; i <= m; ++i)
	{
		PolynNode *s = (PolynNode *)malloc(sizeof(PolynNode));
		assert(s != NULL);
		s->link = NULL;
		cout << "请输入第" << i << "项的系数和指数：>";
		cin >> s->coef >> s->expn;
		_insert(pn, s);
	}
}

void ShowPolyn(Polyn pn)
{																										   
	PolynNode *p = pn;

	while (p != NULL)
	{
		if (p->expn > 1)
		{
			cout << p->coef << "X^" << p->expn;
		}
		else if (p->expn == 1)
		{
			cout << p->coef << "X";
		}
		else
			cout << p->coef;

		p = p->link;
		if (p != NULL)
		{
			if (p->coef > 0)
				cout << "+";
		}
	}
}
								  
int compare(Polyn pa, Polyn pb)
{
	if (pa != NULL && pb == NULL)
		return 1;
	else if (pb != NULL && pa == NULL)
		return -1;
	else  if (pb == NULL && pb == NULL)
		return 0;
	else
	{																										 
		if (pa->expn > pb->expn)
		return 1;
		else if (pa->expn < pb->expn)
			return -1;
		else
			return 0;
	}
}

Polyn PolynAdd(Polyn pa, Polyn pb)
{																								  
	Polyn pc = NULL;										   
	PolynNode  *curPa = pa, *curPb = pb,* tmp = NULL; 
	if (curPa == NULL && curPb != NULL)
		return curPb;
	else if (curPb == NULL && curPa != NULL)
		return curPa;
	else if (curPb == NULL && curPa == NULL)
		return NULL;

	InitPolyn(pc);															  
	while (curPa || curPb)
	{
		tmp = (PolynNode *)malloc(sizeof(PolynNode));
		if (NULL == tmp)
		{
			cout << "分配内存失败！" << endl;
			return NULL;
		}
		switch (compare(curPa, curPb))
		{
		case 1:			 
			tmp->coef = curPa->coef;
			tmp->expn = curPa->expn;
			tmp->link = NULL;
			_insert(pc, tmp);

			curPa = curPa->link;
			break;
		case 0:
			tmp->coef = curPa->coef + curPb->coef;
			tmp->expn = curPa->expn;
			tmp->link = NULL;
			_insert(pc, tmp);

			curPb = curPb->link;
			curPa = curPa->link;
			break;
		case -1:
			tmp->coef = curPb->coef;
			tmp->expn = curPb->expn;
			tmp->link = NULL;
			_insert(pc, tmp);

			curPb = curPb->link;
			break;
		}
	}

	return pc;
}

Polyn PolynSub(Polyn pa, Polyn pb)
{
	PolynNode *curPa = pa, *curPb = pb;
	Polyn pc = NULL;

	InitPolyn(pc);
	while (curPb != NULL)
	{
		curPb->coef *= -1;
		curPb = curPb->link;
	}

	pc = PolynAdd(pa, pb);
	curPb = pb;
	while (curPb != NULL)
	{
		curPb->coef *= -1;
		curPb = curPb->link;
	}

	return pc;
}

Polyn PolynMul(Polyn pa, Polyn pb)
{
	PolynNode *curPa = pa, *curPb = pb;
	PolynNode *tmp = NULL;
	Polyn pc = NULL;

	InitPolyn(pc);
	while (curPa != NULL)
	{
		curPb = pb;
		while (curPb != NULL)
		{
			tmp = (PolynNode *)malloc(sizeof(PolynNode));
			if (NULL == tmp)
			{
				cout << "分配内存失败！" << endl;
				return NULL;
			}		

			tmp->expn = curPa->expn + curPb->expn;
			tmp->coef = curPa->coef * curPb->coef;			
			tmp->link = NULL;
			_insert(pc, tmp);
			curPb = curPb->link;
		}

		curPa = curPa->link;
	}

	return pc;
}