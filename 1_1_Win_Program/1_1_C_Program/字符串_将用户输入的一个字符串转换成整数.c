// 04_04_将用户输入的一个字符串转换成整数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>


int _tmain(int argc, _TCHAR* argv[])
{
	long l;
	char *str = "12345645646";

	l = atol(str);
	printf("intger  = %ld , string is : %s  \n ",l,str);
	system("pause");

	return 0;
}
