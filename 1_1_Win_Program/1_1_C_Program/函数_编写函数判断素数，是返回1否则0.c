// 05_02_��д�����ж��������Ƿ���1����0.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>


int _tmain(int argc, _TCHAR* argv[])
{
	int  prime(int n);
	int s;
	//��������λ��
	s = prime(17);

	printf(" %d \n ",s);

	system("pause");

	return 0;
}
int prime(int n){

	int flag=1;
	for (int i = 2; i < n&&flag==1;i++)
	{
		if (n%i==0)
		{
			flag = 0;
		}
	}
	return flag;
}

