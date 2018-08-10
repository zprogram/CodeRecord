#define SIZE 10 int a[SIZE];
#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)
{

	int nNum = 0;
	printf(" ����һ������ \n ");
	scanf_s("%d", &nNum);

	if (nNum > 0)
	{
		printf(" yes \n ");
	}
	else if (nNum <=0)
	{
		printf(" no \n ");
	}

	printf(" %d \n ",10);

	system("pause");
	return 0;

}
