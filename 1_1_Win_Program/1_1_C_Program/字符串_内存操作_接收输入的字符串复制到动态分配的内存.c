// 04_04_接收输入的字符串复制到动态分配的内存中然后返回值.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <process.h>
#include <malloc.h>


int _tmain(int argc, _TCHAR* argv[])
{
	char hello[40];
	char hello2[40] = "qwertyuiopasdfghjklzxcvbnm";
	char * buffer;
	printf(" 输入字符串 \n ");
	gets_s(hello);

	buffer = (char*)malloc(sizeof(hello2) + 1);              //开辟内存
	if(buffer == NULL){ exit(1); }

	char* i = (char*)memcpy(hello2, hello, sizeof(hello2));  //内存复制

	printf("输入值为： %s \n ",hello);
	printf("复制值为： %s \n ", hello2);
        printf("复制值为： %s \n ", i);                       //此时i指向了hello2的内存地址
	free(buffer);
	
	system("pause");
	
	return 0;
}

