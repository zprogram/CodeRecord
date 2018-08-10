// 04_05_����a��n�����鰴�෴˳����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>
#include <string.h>



void change(int array[], int n){

	int temp, i, j;
	int m = (n - 1) / 2;      //Ҫ�Ի��Ĵ���
	for (i = 0; i <= m;i++)   
	{
		j = n - 1 - i;        //ͷβ����
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
	return;

}


int _tmain(int argc, _TCHAR* argv[])
{
	int i, a[10] = { 3, 7, 9, 11, 0, 6, 7, 5, 4, 2 };
	printf(" The original array \n ");
	for (i = 0; i < 10;i++)
	{
		printf("%d",a[i]);
	}
	printf(" \n ");
	int len = sizeof(a)/sizeof(a[0]);   //�������鳤��
	change(a, len);
	printf(" The array has been inverted \n ");
	for (i = 0; i < 10;i++)
	{
		printf("%d",a[i]);          //���Ŀǰ�����ֵ
	}
	system("pause");
	return 0;
}

