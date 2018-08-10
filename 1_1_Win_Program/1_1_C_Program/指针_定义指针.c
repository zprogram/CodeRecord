// ����ָ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>


int _tmain(int argc, _TCHAR* argv[])
{

	//1.����һ��ָ�룬��ʹ��
	int * p = nullptr;  //nullptr����0
	int nNum = 100;

	//ע�⣺��ַҲ��������
	char ch = 'H'; 

	p = &nNum;

	//���
	printf(" %x \n ",p);
	printf(" %x \n ",*p);
	
	//��ֵ
	*p = 200;

	//ָ����ص�����
	printf("ָ���ֵ����ַ��: %x \n ", p);
	printf("ָ���ֵָ�������(int): %x \n ", *p);
	printf("ָ������ĵ�ַ����ַ��: %x \n ", &p);
	printf("int�����ĵ�ַ����ַ��: %x \n ", &nNum);

	//2.ָ�������
	printf("ָ���ֵ����ַ+1��: %x \n ", p+1);
	printf("ָ��Ľ����ã�+1��: %x \n ", *p + 1);

	//3.һ��ָ����һά����Ĺ�ϵ
	//�����������׵�ַԪ�صĵ�ַ
	int arr[10];
	int * pArr = arr;

	//��ά������ָ��
	//int arr1[10][10];
	//int(*p)[10] = arr1;


	////	��ά����
	//int arr2[10][10][30];
	//int(*p)[10][30] = arr2;


	//���ַ�ʽ����ָ�����飬arr[i] <-> *(arr+1)

	for (int i = 0; i < 10;i++)
	{
		printf(" %d \n ",arr[i]);  //1.�±������ []��ʽ��������
		printf(" %d \n ", pArr[i]);   //ʹ��������/��ַ
		printf(" %d \n ", *(arr + 1)); //2.ָ��ķ�ʽ��������
		printf(" %d \n ", *(pArr + i)); //ʹ�������� /��ַ
	}

	//ʹ�ñ�����ַ��ָ��Ա�
	int a;
	scanf_s("%d", &a);

	char str[100];
	//ָ����ǵ�ַ�����Բ���Ҫ&���ţ�
	scanf_s("%s",str,100);







	system("pause");

	return 0;
}

