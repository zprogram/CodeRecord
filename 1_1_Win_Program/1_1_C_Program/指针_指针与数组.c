// 05_00_ָ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>
#include  <cstring>
#include <crtdbg.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char  str[][10] = { "hello", "Google"};
	char * p = str[0];
		printf(" %d\n ",strlen(++p));

	system("pause");

	return 0;
}