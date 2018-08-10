// 05 д����һ���ַ�����ȥ������Ŀո�ĺ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include <string.h> 
#include <stdio.h>



int _tmain(int argc, _TCHAR* argv[])
{
	void  deblank(char string[]);  /*�����������*/

	char str[200];


	

	gets_s(str);
	
	deblank(str);
	//deblank("hello world");


/*
	printf("The line entered was: %s\n", str);*/


	system("pause");

	return 0;
}
void deblank(char string[]){

	int len,i;

	len = strlen(string);

	for (i = 0; i < len; i++)
	{
		if (string[i]!= ' ')
		{
			printf("%c", string[i]);
		}
		
	}


	


}