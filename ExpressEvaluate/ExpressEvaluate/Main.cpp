
#include"ExpressEvaluate.h"

int main()
{
	char *exp = "4-8*3-10/5#";
	//bool flag = Cheak(exp);
	int res = EvaluateExpression(exp);
	cout<< exp << " = "<<res<<endl;
	return 0;
}