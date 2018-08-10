// 04_02_���������ж�7�ı�����β������7����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>


int _tmain(int argc, _TCHAR* argv[])
{
	int nNum = 50;

	if ((nNum%7==0)||(nNum%10==7))
	{
		printf(" yes");
	}
	else{
		printf(" no ");
	}
	system("pause");
	return 0;
}

