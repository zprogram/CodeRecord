#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int sum = 0;
	int nNum,Tmep;




	printf(" ����һ���������ж��ж��ٸ�λ��1 \n ");
	scanf_s("%d", &nNum);

loop: if(nNum)
	{
		Tmep = nNum % 10;
		nNum = nNum / 10;
		if (Tmep==1)
		{
			sum++;
		}
		goto loop;

	}


	printf(" �������������� ��    %d    ����λ��1 \n ",sum);
    system("pause");
    return 0;

}