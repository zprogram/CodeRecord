// 06 ͳ�Ʋ�ͬ�ַ�����Ƶ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>

int main()
{
	char a = 0;
	int num_count = 0;
	int space_count = 0;
	int other_count = 0;
	//ע��˴�������д��a=getchar(),Ȼ��while(a!='\n'),������ֻ������һ�У�Ȼ�������ѭ��
	while ((a = getchar()) != '\n')
	{
		if (a >= '0'&&a <= '9')
		{
			num_count++;
		}
		else if (a == ' ')
		{
			space_count++;
		}
		else
		{
			other_count++;
		}
	}
	printf("num_count=%d\n", num_count);
	printf("space_count=%d\n", space_count);
	printf("other_count=%d\n", other_count);
	system("pause");
	return 0;
}
