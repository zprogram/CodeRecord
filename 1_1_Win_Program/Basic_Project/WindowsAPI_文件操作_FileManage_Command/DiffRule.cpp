#include "stdafx.h"
#include "DiffRule.h"
#include <windows.h>
#include <fstream>  
#include <string>  
#include <iostream>  
using namespace std;

CDiffRule::CDiffRule()
{
}






/************************************
* Access:    public 
* ��������:  DiffRuleProcess
* ��������:  ��Ҫ�Աȹ����ܺ���

* �����б�:
*   char * nPara1: ��һ���������ļ���·�����ж�������������
*   char * nPara2: �ڶ����������ļ���·����ȡ��������������
*   $
* ����ֵ:    int
* 
*************************************/

int CDiffRule::DiffRuleProcess(char * nPara1, char * nPara2)
{
	// ���ж�·���ǲ���Ϊ��ȷ��
	if ( !ifstreamProcess(nPara1))
	{
		system("cls");
		printf("\n %s \n�ļ�·�������ڡ�", nPara1);
		return 0;
	}
	// ���ж�������·���ǲ���Ϊ��ȷ��
	if (!ifstreamProcess(nPara2))
	{
		system("cls");
		printf("\n %s \n�ļ�·�������ڡ�", nPara2);
		return 0;
	}

	// ��ʼ���Աȵ�����
	TargetRule(nPara1);
	DiffRule(nPara2);

	// ��ʼ�����Ա�
	vecFileProcess();

    // begindiff();

	
	return 0;
}

/************************************
* Access:    public
* ��������:  ifstreamProcess
* ��������:  ������ļ�������

* �����б�:
*   $
* ����ֵ:    bool
*
*************************************/

bool CDiffRule::ifstreamProcess(char* nFile_Name)
{

	//char*תwchar*
	const size_t cSize = strlen(nFile_Name) + 1;
	wchar_t* wFile_Name = new wchar_t[cSize];
	mbstowcs(wFile_Name, nFile_Name, cSize);

	HANDLE pFile = CreateFile(wFile_Name, GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	//�ж��ļ��Ƿ����
	if (pFile == INVALID_HANDLE_VALUE)
	{
		printf("δ�ҵ��ļ�,�����ļ��Ƿ����\n %s", nFile_Name);
		return false;
	}

	return true;
}

/************************************
* Access:    public 
* ��������:  TargetRule
* ��������:  ��ȡ�ж��������ɵ��ļ�������

* �����б�:
*   char * nFile_name:�ļ��������ж�ȡ
*   $
* ����ֵ:    bool
* 
*************************************/

bool CDiffRule::TargetRule(char * nFile_name)
{
	ifstream in(nFile_name);
	string filename;
	string line;

	//�����ļ�����
	int num = 0;

	if (in) // �и��ļ�  
	{
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�  
		{
			vecTatgetRule.push_back(line);
			num++;

		}
	}
	else // û�и��ļ�  
	{
		cout << "no such file" << endl;
	}
	cout <<"�Ա��ļ�����Ϊ"<< num << endl;

	return false;
}

/************************************
* Access:    public 
* ��������:  DiffRule
* ��������:  ��ȡ���ػ������ɵ��ļ�������

* �����б�:
*   char * nFile_Name:�ļ��������ж�ȡ
*   $
* ����ֵ:    bool
* 
*************************************/

bool CDiffRule::DiffRule(char* nFile_Name)
{
	ifstream in(nFile_Name);
	string filename;
	string diff_line;

	//�����ļ�����
	int num = 0;

	if (in) // �и��ļ�  
	{
		while (getline(in, diff_line)) // line�в�����ÿ�еĻ��з�  
		{

			vecDiffRule.push_back(diff_line);

			num++;

		}
	}
	else // û�и��ļ�  
	{
		cout << "no such file" << endl;
	}


	cout << "������Ա��ļ�����Ϊ" << num << endl;

	return false;

}

/************************************
* Access:    public 
* ��������:  vecFileProcess
* ��������:  �Ա������ļ����ظ���ֵ��Ȼ��ȥ�������¡��ж������ļ������в��ظ����ļ���

* �����б�:
*   $
* ����ֵ:    bool
* 
*************************************/

bool CDiffRule::vecFileProcess()
{
	int nCount = 0;


	//ɾ�����Ƶ�
	for (size_t i = 0; i< vecDiffRule.size(); i++)
	{
		for (size_t j=0;j<vecTatgetRule.size();)
		{

			int nRet = strcmp(vecDiffRule[i].c_str(), vecTatgetRule[j].c_str());

			if (nRet==0)
			{
				//vecTatgetRule.erase(vecTatgetRule.begin()+j);
				//cout << vecTatgetRule[j].c_str() << "Ϊ��ͬ�ļ�" << endl;
				vecTatgetRule.erase(vecTatgetRule.begin() + j);

			}
			else
			{
				j++;
			}
		}

	}

	//�����ͬ��
	for (size_t i=0;i<vecTatgetRule.size();i++)
	{
		cout << "��ͬ��Ϊ��" << vecTatgetRule[i].c_str()  <<endl;
	}

	system("pause");
	return false;
}


CDiffRule::~CDiffRule()
{
}
