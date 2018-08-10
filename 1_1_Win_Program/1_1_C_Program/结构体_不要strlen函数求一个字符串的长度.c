// 05_04_��Ҫstrlen������һ���ַ����ĳ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>

struct TestA
{
	float math;
	float English;
	float Chinese;
}xiaohong = {2,2,2};
struct TestB
{
	char Name[20];
	int StuNumb;
	TestA objA;
};
TestA stc1;
TestB stc2;  //ȫ�ֱ���


int _tmain(int argc, _TCHAR* argv[])
{
	//TestA xiaohong = { 2, 2, 175 };
	printf("TestA Ϊ��%d \n", sizeof(TestA));
	printf("TestB Ϊ��%d \n", sizeof(TestB));
	printf("����:%f \n", xiaohong.math);
	printf("�Ա�:%f \n", xiaohong.English);
	printf("����:%f \n", xiaohong.Chinese);

	system("pause");

	return 0;
}

