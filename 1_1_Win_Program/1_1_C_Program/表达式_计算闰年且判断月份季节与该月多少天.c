#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int nYear, nMonth;

	printf(" ����������·ݣ���ʽ�硾2016 8������2016 12�� \n ");
	scanf_s("%d %d", &nYear,&nMonth);

	if ((nYear % 4 == 0 && nYear % 100 != 0) || (nYear % 400 == 0))
	{

		printf(" %d Ϊ���� \n ", nYear);
		switch (nMonth)
		{
		case 1 :  printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 2:   printf(" �ü���Ϊ���죬�����������29�� \n "); break;
		case 3:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 4:   printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 5:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 6:   printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 7:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 8:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 9:   printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 10:  printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 11:  printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 12: printf(" �ü���Ϊ���죬�����������31�� \n "); break;

		default:
			break;
		}
	}
	else
	{
		printf(" %d ��Ϊ���� \n ", nYear);
		switch (nMonth)
		{
		case 1:  printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 2:   printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 3:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 4:   printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 5:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 6:   printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 7:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 8:   printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 9:   printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 10:  printf(" �ü���Ϊ���죬�����������31�� \n "); break;
		case 11:  printf(" �ü���Ϊ���죬�����������30�� \n "); break;
		case 12: printf(" �ü���Ϊ���죬�����������31�� \n "); break;

		default:
			break;
		}
	}

    system("pause");
    return 0;

}