// 04_06_����һ������̹����Ϣ�Ľṹ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <process.h>

typedef struct _TankInfo
{

	int nNum;
	char szName[20];
	int weapon;
	int nScore;
}TankInfo, *TankINFO;

int _tmain(int argc, _TCHAR* argv[])
{

	TankInfo  zzz = { 1, "zzz", 5, 100 };
	printf(" ���룺 %d \n ̹������  %s \n  �����ǣ� %d \n  �ɼ��ǣ� %d \n",zzz.nNum,zzz.szName,zzz.weapon,zzz.nScore);
	system("pause");
	return 0;
}

