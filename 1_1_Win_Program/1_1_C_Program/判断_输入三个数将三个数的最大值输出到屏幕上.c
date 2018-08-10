// 04_01_�����������������������ֵ�������Ļ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>


int _tmain(int argc, _TCHAR* argv[])
{
	int a = 3, b = 2, c = 4,d,max;

	d = a > b ? a : b;
	max = d > c ? d : c;
	printf(" %d \n ",max);

	system("pause");

	return 0;
}

