#include<stdio.h>

#include<stdlib.h>

#include<string.h>


int main(void)

{
	int nYear;

	printf(" ����һ������ \n ");
	scanf_s("%d", &nYear);

	if ((nYear % 4 == 0 && nYear % 100 != 0) || (nYear % 400 == 0))
	{

		printf(" %d Ϊ���� \n ", nYear);
	} 
	else
	{
		printf(" %d ��Ϊ���� \n ", nYear);
	}
    system("pause");
    return 0;

}