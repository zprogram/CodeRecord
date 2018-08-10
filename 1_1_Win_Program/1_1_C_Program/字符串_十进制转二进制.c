#include <stdio.h>
#include <stdlib.h>
void dec_bin(long int num)   // Function Definition
{
	long int rem[50], i = 0, length = 0;
	while (num > 0)
	{
		rem[i] = num % 2;  //���������
		num = num / 2;
		i++;
		length++;
	}

	for (i = length - 1; i >= 0; i--)
		printf("%ld", rem[i]);

	printf(" \n ");
}

int main()
{

	int nNumA;
	int nNumB = 15 ;   // 0x0F �� ������Ϊ00001111
	int nResult;
	/*
	 *	������������
	 */
	printf("Enter an integer number\n");
	scanf_s("%d", &nNumA);
	nResult = nNumA^nNumB;
	printf(" %d \n ", nResult);
	//ʮ����ת������
	dec_bin(nNumA);
	
	system("pause");
}