#include <iostream>
using namespace std;

/*
long Fib(int n)
{
	long res = 1, pRes1 = 1, pRes2 = 1;
	if (0 == n) 
		res = 0;t
	for (int i = 3; i <= n && n > 2; ++i)
	{
		pRes2 = pRes1;
		pRes1 = res;
		res = pRes1 + pRes2;
	}
	
	return res;
}
*/

long Fib(int n)
{
	if (0 == n)
		return 0;
	else if (0 < n && n <= 2)
		return 1;
	else
		return Fib(n-1)+Fib(n-2);
}

int main()
{
	cout << Fib(6);

	return 0;
}
