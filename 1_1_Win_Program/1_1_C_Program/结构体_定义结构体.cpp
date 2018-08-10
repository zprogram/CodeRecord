// 5_����ṹ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "stdlib.h"
#include  <string.h>


//1.����ṹ������
//�﷨1�� ���Ƽ�ʹ���﷨
//struct _PERSON
//{
//	char name[20];
//	char sex;
//	int age;
//	float height;
//}stc_xiaoming = {};


typedef struct _PERSON
{
	char name[20];
	char sex;
	int age;
	double height;
}newName;

newName stc1;
_PERSON stc2; //ȫ�ֱ���


int _tmain(int argc, _TCHAR* argv[])
{

	//2.����ṹ�����������ʼ���ڴ�Ϊ0
	_PERSON xiaolv;   //�ֲ�����

	//�ͷ��ڴ�ռ䣬����0
	memset(&xiaolv, 0, sizeof(_PERSON));


	// ��ʼ���ṹ�����
	_PERSON xiaohong = { "С��", 'M', 18, 3.14 };
	xiaolv = xiaohong;
	printf("%d", sizeof(_PERSON));


	//3.ʹ�ýṹ��
	xiaolv.age = 18;
	xiaolv.height = xiaohong.height;
	xiaolv.sex = 'F';

	strcpy_s(xiaolv.name,20, xiaohong.name);

    printf(" ���֣�%s\n ",xiaolv.name);
	printf(" �Ա�%c\n ", xiaolv.sex);
	printf(" ���䣺%d\n ", xiaolv.age);
	printf(" ��� ��%f\n ", xiaolv.height);



	//4.����ṹ������

	_PERSON per2[] = { {"lilei",'M',25,1.8},
	                     { "hanmeimei", 'F', 23, 165.8 },
	
                   };

	int struct_len = sizeof(per2) / sizeof(per2[0]);

	//5.ʹ�ýṹ������
	for (int i = 0; i < _countof(per2);i++)
	{

		printf(" ���֣�%s \n ", per2[i].name);
		printf(" �Ա�%c \n ", per2[i].sex);
		printf(" ���䣺%d \n ", per2[i].age);
		printf(" ��ߣ�%f \n ", per2[i].height);

	}

	system("pause");

	return 0;
}
