// 04 ��д���׵�printf����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include <string.h>
#include <stdarg.h>

int main()
{

	int MyPrintf(char szFormat[], int nNumb);

	int dec = 1234;
	MyPrintf("%d", dec);
	system("pause");

	return 0;
}
int MyPrintf(char szFormat[], int nNumb){

	int s;
	s = printf(szFormat, nNumb);
	return s;

}