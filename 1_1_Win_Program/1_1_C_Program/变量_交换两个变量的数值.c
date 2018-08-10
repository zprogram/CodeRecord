#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int a = 10;
	int b = 20;
	int t;

	printf("a��ԭʼֵ��%d \n",a);
	printf("b��ԭʼֵ��%d \n", b);
	printf("����ֵ��ʼ \n");
	t = a;
	a = b;
	b = t;
	printf("a�Ľ���ֵ��%d \n", a);
	printf("b�Ľ���ֵ��%d \n", b);
	printf("����ֵ����\n");


    system("pause");
    return 0;

}