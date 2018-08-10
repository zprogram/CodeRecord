// 01 20160905-15PB-Day004�ϻ���_����10���ڵ����Ľ׳�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"

int _tmain(int argc, _TCHAR* argv[])
{

	int sum = 1;
	int nNum = 0;
	int Tmep;
	int Counter = 0;


	for (int i = 1; i <= 10; i++)
	{
		sum = sum * i;
	}
	printf(" 10*9*8*7*6*5*4*3*2*1�Ľ��Ϊ�� %d \n ", sum);

	system("pause");

	return 0;
}
