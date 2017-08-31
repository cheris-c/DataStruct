#include "Polyn.h"
#include <iostream>
using namespace std;

int main()
{
	Polyn pa;
	Polyn pb;
	Polyn pc;

	InitPolyn(pa);
	InitPolyn(pb);
	InitPolyn(pc);

	int m;
	int select = 1;
	while (select)
	{
		cout << "***********************************" << endl;
		cout << "*[1]创建多项式pa  [2]创建多项式pb *" << endl;
		cout << "*[3]显示多项式pa  [4]显示多项式pb *" << endl;
		cout << "*[5]多项式相加    [6]多项式相减   *" << endl;
		cout << "*[7]多项式相乘    [0]退出系统     *" << endl;
		cout << "***********************************" << endl;
		cout << "请选择:>";
		cin >> select;

		switch (select)
		{
		case 1:
			cout << "请输入多项式的项数：>";
			cin >> m;
			CreatePolyn(pa, m);
			break;
		case 2:
			cout << "请输入多项式的项数：>";
			cin >> m;
			CreatePolyn(pb, m);
			break;
		case 3:
			cout << "pa = ";
			ShowPolyn(pa);
			cout << endl;	
			break;
		case 4:
			cout << "pb = ";
			ShowPolyn(pb);
			cout << endl;
			break;
		case 5:												 
			pc = PolynAdd(pa, pb);
			cout << "pc = ";
			ShowPolyn(pc);
			cout << endl;
			break;
		case 6:
			pc = PolynSub(pa, pb);
			cout << "pc = ";
			ShowPolyn(pc);
			cout << endl;
			break;
		case 7:
			pc = PolynMul(pa, pb);
			cout << "pc = ";
			ShowPolyn(pc);
			cout << endl;																	 
			break;
		case 0:
			exit(1);
			break;
		}
	}

	return 0;
}