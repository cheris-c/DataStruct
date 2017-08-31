#include<iostream>
#include<windows.h>
#include"bigint.h"
using namespace std;


char* bttoStr(BigInt &bt)
{
	int size = bt.size();
	char *str = (char *)malloc(size + 2);
	memset(str, 0, size + 2);
	int j = 1;

	for (int i = size; i > 0; --i)
		cout << (int)bt[i] << " ";

	if (bt.GetSymbol() == POSITIVE)					   		

		str[0] = ' ';
	else
		str[0] = '-';

	str[j] = '\0';

	return str;
}

int main()
{
	BigInt bt, bt1(37), bt2(5);
	BigInt::Mod(bt, bt1, bt2);
	//bt1 -= bt2;
	cout<<"bt = "<<bt<<endl;
	char *str =bt.toString();
	printf("%s\n", str);
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}

	return 0;
}

/*
#define RAND

#ifdef RAND 

void main()
{
	BigInt bt,bt1,bt2;
	bt1.LoadData(3);
	cout<<"bt1="<<bt1<<endl;
	Sleep(1000);
	bt2.LoadData(2);
	cout<<"bt2="<<bt2<<endl;
	//bt2.PrintData();

	BigInt::Mod(bt, bt1, bt2); //bt = bt1 - bt2;
	//bt1 *= bt2;
	cout<<"bt= "<<bt<<endl;
	//bt.PrintData();
}

#else

void main()
{
	BigInt bt, bt1(85), bt2(68);
	BigInt::Div(bt, bt1, bt2);
	//bt1 *= bt2;
	cout<<"bt = "<<bt<<endl;
}

#endif
  */