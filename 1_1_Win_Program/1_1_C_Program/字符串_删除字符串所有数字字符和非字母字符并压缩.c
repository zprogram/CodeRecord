// 04_03_ɾ���ַ������������ַ��ͷ���ĸ�ַ���ѹ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>

void replaceA_Z(char * str);

int _tmain(int argc, _TCHAR* argv[])
{

	char str[40] = "abc12ef5ghij8#%%yz";   //���ﲻ�ܶ���char* ָ��ֱ��ָ���ַ�����������Ϊָ��ָ���ֵ���ܸı�  

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
	printf(" ��ȷ���Ӧ��Ϊ��acdefghijyz \n");

	
}
	

//char * replaceA_Z(char * str){
//	char *p1, *p2;
//	p1 = str;
//	p2 = str;
//
//	//���������������ν���ĸ�ַ����Ƶ��ַ�����  
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