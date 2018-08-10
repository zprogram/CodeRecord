#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int nNum;
	printf(" \t\t\t**************************************  \n ");
	printf(" \t\t\t*           1   One Player           *  \n ");
	printf(" \t\t\t*           2   Two Player           *  \n ");
	printf(" \t\t\t*           3   Edit Player          *  \n ");
	printf(" \t\t\t*           4   Chose Player         *  \n ");
	printf(" \t\t\t**************************************  \n ");

	printf(" ��ѡ������Ӧ������ ����һ������ \n ");
	scanf_s("%d", &nNum);

	switch (nNum)
	{
	case 1 : printf(" ��ѡ���� One Player \n " ); 
		break;
	case 2 : printf(" ��ѡ���� Two Player \n ");
		break;
	case 3 : printf(" ��ѡ���� Edit Player \n ");
		break;
	case 4 : printf(" ��ѡ���� Chose Player \n ");
		break;
	default:
		break;
	}
    system("pause");
    return 0;

}