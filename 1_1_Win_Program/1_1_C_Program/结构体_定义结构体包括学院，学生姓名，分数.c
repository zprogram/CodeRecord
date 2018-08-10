// 04_05_����ṹ�����ѧԺ��ѧ������������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>

typedef struct _StuInfo
{

	int nNum;
	char szName[20];
	char nScore;
}STUINFO,*PSTUINFO;
int _tmain(int argc, _TCHAR* argv[])
{
	_StuInfo student1 = { 25, "liming", 88 };
	printf(" ѧ������Ϊ��%d\n ѧ������Ϊ��%s \n �ɼ�Ϊ��%d \n",student1.nNum,student1.szName,student1.nScore);
	system("pause");
	return 0;
}

