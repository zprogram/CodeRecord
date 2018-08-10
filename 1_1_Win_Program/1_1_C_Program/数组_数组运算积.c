// 03 ���������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"

int _tmain(int argc, _TCHAR* argv[])
{

	int arrayA[10];
	int arrayB[10];
	int arrayC[10];
	int i;


	/*1.��ȡ����A��ʮ��Ԫ��,���������*/

	printf("��������������A�е�10��������\n");
	for (i = 0; i < 10; i++){
		printf(" arrayA[%d] == \n ", i);
		scanf_s("%d", &arrayA[i]);
	}
	system("cls");
	printf("����A�����10������Ϊ��\n");
	for (i = 0; i < 10; i++){
		printf("%d ", arrayA[i]);

	}


	/*2.��ȡ����B��ʮ��Ԫ�أ����������*/

	printf("��������������B�е�10��������\n");
	for (i = 0; i < 10; i++){
		printf(" arrayB[%d] \n ", i);
		scanf_s("%d", &arrayB[i]);
	}

	printf(" \n");
	printf("����B�����10������Ϊ��\n");
	for (i = 0; i < 10; i++){
		printf("%d ", arrayB[i]);
	}
	printf(" \n");



	/*3.������A������B��ֵ��������C�����������*/

	printf("����CΪarrayA[]��arrayB[]�Ļ���\n");
	for (i = 0; i < 10; i++){
		arrayC[i] = arrayA[i] * arrayB[i]; //�õ���˽������C����.
		printf("arraryC[%d] == %d \n", i, arrayC[i]);
	}



	printf("\n");

	system("pause");

	return 0;
}