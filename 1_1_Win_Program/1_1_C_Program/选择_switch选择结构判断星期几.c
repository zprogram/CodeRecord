#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int nNum = 0;
	printf(" ����һ������ \n ");
	scanf_s("%d", &nNum);

	switch (nNum)
	{
	case 1: printf(" %d ��������һ \n ", nNum);
		break;
	case 2: printf(" %d �������ڶ� \n ", nNum); 
		break;
	case 3: printf(" %d ���������� \n ", nNum); 
		break;
	case 4: printf(" %d ���������� \n ", nNum); 
		break;
	case 5: printf(" %d ���������� \n ", nNum); 
		break;
	case 6: printf(" %d ���������� \n ", nNum); 
		break;
	case 7: printf(" %d ���������� \n ", nNum); 
		break;

	default:
		break;
	}
    system("pause");
    return 0;

}