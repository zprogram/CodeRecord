// 04_04_����������ַ������Ƶ���̬������ڴ���Ȼ�󷵻�ֵ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>
#include <malloc.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char hello[40];
	char hello2[40] = "qwertyuiopasdfghjklzxcvbnm";
	char * buffer;
	printf(" �����ַ��� \n ");
	gets_s(hello);

	buffer = (char*)malloc(sizeof(hello2) + 1);              //�����ڴ�
	if(buffer == NULL){ exit(1); }

	char* i = (char*)memcpy(hello2, hello, sizeof(hello2));  //�ڴ渴��

	printf("����ֵΪ�� %s \n ",hello);
	printf("����ֵΪ�� %s \n ", hello2);
        printf("����ֵΪ�� %s \n ", i);                       //��ʱiָ����hello2���ڴ��ַ
	free(buffer);
	
	system("pause");
	
	return 0;
}

