#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int a, b, c,d,max;
	scanf_s("%d %d %d", &a, &b, &c);
	d = (a > b) ? a : b;
	max = c > d ? c : d;
    printf("���ֵΪ:%d \n ",max);
	system("pause");
	return 0;
}
