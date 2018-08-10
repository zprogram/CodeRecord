#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	long nNum;
	printf("enter two number \n");
	scanf_s("%d", &nNum);

	/*����1����ͬʱ��3��5��7���� */
	/* �ܱ�3,5,7���� */
	if (nNum % 3 == 0 && nNum % 5 == 0 && nNum % 7 == 0)
	{
		printf("%d�ܱ�3,5,7���������� \n", nNum);
		/*�ܱ�5,7����*/
		if (nNum % 5 == 0 && nNum % 7 == 0)
		{
			printf("%d �ܱ�5,7���������� \n", nNum);
		}
		else if (nNum % 3 == 0)
		{
			printf("%d�ܱ�3���������� \n", nNum);
		}
		else if (nNum % 5 == 0)
		{
			printf("%d�ܱ�5���������� \n", nNum);
		}
		else if (nNum % 7 == 0)
		{
			printf("%d�ܱ�7���������� \n", nNum);
		}else
		{
			printf("%d ���ܱ�3,5,7���������� \n", nNum);
		}
	}

	/*����2���ܱ���������������*/
	if (nNum % 3 == 0 && nNum % 5 == 0)
	{
		printf("%d �ܱ�3��5���������� \n",nNum);
	}
	else if (nNum % 5 == 0 && nNum % 7 == 0)
	{
		printf("%d �ܱ�5��7���������� \n", nNum);
	}else if (nNum % 3 == 0 && nNum % 7 == 0)
	{
		printf("%d �ܱ�3��7���������� \n", nNum);
	}
	else{
		printf("%d ����ͬʱ������������������ \n", nNum);
	}

	/*����3���ܱ�����һ��������*/
	if (nNum % 3 == 0 )
	{
		printf("%d �ܱ�3���������� \n", nNum);
	}
	else if (nNum % 5 == 0 )
	{
		printf("%d �ܱ�5���������� \n", nNum);
	}
	else if (nNum % 7 == 0)
	{
		printf("%d �ܱ�7���������� \n", nNum);
	}
	else
	{
		printf("%d ���ܱ�3,5,7 �κ�һ���������������� \n", nNum);
	}

	
    system("pause");
    return 0;

}