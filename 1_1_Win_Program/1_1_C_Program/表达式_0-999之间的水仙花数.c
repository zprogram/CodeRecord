#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int nNum, hun, ten, gw, sum;
	for (nNum = 100; nNum < 999; nNum++)
	{
		hun = nNum / 100;                       //ȡ��λ
		ten = nNum / 10 % 10 ;                  //ȡʮλ
		gw = nNum % 10;                         //ȡ��λ
		sum = hun*hun*hun + ten*ten*ten + gw*gw*gw;
		if (nNum == sum)
		{
			printf(" %d ��ˮ�ɻ��� \n ",nNum);
		}
	}

    system("pause");
    return 0;

}