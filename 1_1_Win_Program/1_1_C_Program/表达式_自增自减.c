#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>

#include<stdlib.h>

#include<string.h>





int main()

{
	//int i = 10;

	////������ͬʱ���������˱�����㣬��ô���Ȳ������㣬��������
	//printf("%d", i++); //���10
	////������ͬʱ���������˱�����㣬��ô�����������ٲ������㣻
	//printf("%d", ++i); //���12

	int num = 2, i = 6;
	do
	{
		i--;       
		num++;         //   num = 3 4 5
		 
	} while (--i);     //i = 4 2 0
	printf("%d",num);  //���Ϊ5
	system("pause");
   return 0;
}