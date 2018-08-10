#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	double a, b, c;
	printf("���������������ߵĳ��� \n ");
	scanf_s("%lf %lf %lf", &a,&b,&c);
	if (a + b > c&&a + c > b&&b + c > a)
	{
		if (a == b&&b == c){
			printf("�ȱ�������\n");
		}
		else if ((a == b&&b != c) || (b == c&&b != a) || (a == c&&a != b))
		{
			printf(" ����������\n ");
		}
		else{
		
			if (a*a+b*b==c*c||a*a+c*c==b*b||b*b+c*c==a*a)
			printf(" ֱ��������\n ");
		
		}

	}
	else{
		printf(" ���ܹ���������\n ");
	}
    system("pause");
    return 0;

}