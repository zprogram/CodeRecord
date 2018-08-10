#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int a, b, c, d, e,i , aver ;

	for (i = 1; i <= 6;i++)
	{
		printf(" �����%d��ѧ���ɼ�\n ",i);
		scanf_s("%d%d%d%d%d", &a, &b, &c , &d, &e);
		aver = (a + b + c + d + e) /5;
		printf("\t ��%d����ͬѧ�ɼ��ֱ��ǣ�%d %d %d %d %d  \n\t ƽ���ɼ��ǣ� %d \n ",i,a,b,c,d,e,aver);
	}


	system("pause");
    return 0;

}