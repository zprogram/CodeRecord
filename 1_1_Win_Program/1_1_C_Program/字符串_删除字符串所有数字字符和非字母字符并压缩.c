// 04_03_删除字符串所有数字字符和非字母字符并压缩.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>

void replaceA_Z(char * str);

int _tmain(int argc, _TCHAR* argv[])
{

	char str[40] = "abc12ef5ghij8#%%yz";   //这里不能定义char* 指针直接指向字符串常量，因为指针指向的值不能改变  

	replaceA_Z(str);
    //	printf("%s\n", replaceA_Z(str));


	system("pause");
	return 0;
}
void replaceA_Z(char *str){

	int len = strlen(str) + 1;
	for (int i = 0; i < len;i++)
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')){
			printf("%c", str[i]);
		}
	}
	printf(" 正确结果应该为：acdefghijyz \n");

	
}
	

//char * replaceA_Z(char * str){
//	char *p1, *p2;
//	p1 = str;
//	p2 = str;
//
//	//基本方法就是依次将字母字符复制到字符串中  
//	while (*p1 != '\0'){
//		if ((*p1 >= 'a' && *p1 <= 'z') || (*p1 >= 'A' && *p1 <= 'Z')){
//			*p2++ = *p1;
//		}
//		p1++;
//	}
//	*p2 = '\0';
//
//	return str;
//}