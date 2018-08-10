// 04_03_��ȡint���������������λ���ٸ�λ��1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>

//�������ж��ٸ�1
void toralone(int x)
{
	int count = 0;
	int x1;
	//int x2;
	while (x)
	{
		x1 = x % 2 ;            //���������������
		//x2 = x / 10; 
		if (x1==1)
		{
			count++;
		}
		x /= 2;                 //���ұ��ƶ�һλ
	}
	printf("count= %d \n ",count);
}



int _tmain(int argc, _TCHAR* argv[])
{
	toralone(4);
	system("pause");
	return 0;
}

