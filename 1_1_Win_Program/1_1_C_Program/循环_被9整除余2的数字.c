#include<stdio.h>

#include<stdlib.h>

#include<string.h>

int main(void)

{
	int i;
	
	for (i = 0; i < 100;i++)
	{
		if (i % 9 == 2){
		printf(" %d ���ܱ�9������2������ \n ",i);
		}
	}
    system("pause");
    return 0;

}