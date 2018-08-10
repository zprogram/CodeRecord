// FileManage_Command.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "stdlib.h"
#include "stdio.h" 
#include "iostream"
#include "BrowseDir.h"
#include <windows.h>
#include  <fstream>
#include  < string >
#include "DiffRule.h"
#include "CopyFileToDir.h"
using namespace std;



/************************************
* Access:    public 
* ��������:  usage
* ��������:  ����÷�˵������

* �����б�:
*   $
* ����ֵ:    void
* 
*************************************/

void usage() 
{
	printf("\nauthor:zzzhhh\n");
	printf("\nExample: \n\n");
	printf("\t1.����������:\n\tFileManage.exe -Find Ҫ���ҵ�Ŀ¼ -Output Ҫ���ɵ��ļ�\n\t -name ֻ�����ļ���|| -size �����ļ���+��С|| -hash �ļ�MD5ֵ \n\n");
	printf("\tFileManage.exe -Find C:\\Windows -Output C:\\target.txt  -name || -size ||-hash \n\n");
	printf("\t2.�Ա�Ŀ¼:\n\tFileManage.exe -diff �Աȵ�Ŀ¼ -Rule �������ɵĹ���\n\t -L Ĭ�϶Ա�ÿ�� -B �Ա�ÿ�ֽ�\n\n");
	printf("\tFileManage.exe -Diff target.txt -Rule diff_Name.txt\n\t -L||-B \n\n");
	printf("\t3.���������ļ���ĳ��Ŀ¼��:\n\t -C �����ļ�����.txt -Output ���ƹ�ȥ��Ŀ¼\n\n");
	printf("\tFileManage.exe -C target.txt -Output D:\\save-dir \n\n");
}


int main(int argc, char* argv[])
{

	//Debug������Ϣ
	//argc = 5;
	//argv[1] = "-diff";                                  //����1  -find �����ļ�   -diff �Ա�Ŀ¼ -C �����ļ���
	//argv[2] = "D:\\windows-dir.txt";                    //����2  ��Ҫ�����ļ�����Ŀ¼
	//argv[3] = "-rule";                                //����3  -output ����ļ� -rule ѡ�����
	//argv[4] = "D:\\target.txt";                         //����4  ������ļ�����ŵ�·��
	//argv[5] = "-hash";                              //����5  -name �ļ���  -size �ļ���+��С -hash �ļ���+md5



	//Ŀ¼�����
	CBrowseDir BrowseDir;
	//����Ա���
	CDiffRule DiffRule;
	//Ŀ¼�ļ�����
	CopyFileToDir CopyfFile;

	//����˵��
	usage();


	//Debug �жϲ����Ƿ����ھ����Ƿ�������
	if (argc < 5)
	{
		printf("�������벻��ȷ������������!\n");
		return 0;
	}


	// �жϵ�һ���������Ƿ�Ϊ���һ�Ա�
	if ((strcmp(argv[1], "-Find") == 0) || 
		(strcmp(argv[1], "-find") == 0))
	{

		// �жϵڶ����������Ƿ�Ϊ��������
		if ((strcmp(argv[3], "-Output") == 0) ||
			(strcmp(argv[3], "-output") == 0))

		{
			//��������
			system("cls");


			if (argc !=6)
			{
				BrowseDir.BrowseDir_function(argv[1], argv[2], argv[3], argv[4], g_FILE_NAME);
			}


			//��Ҫ���ܺ���ʵ�� - �����ļ���
			if ((strcmp(argv[5], "-NAME") == 0) ||
				(strcmp(argv[5], "-name") == 0)) 
			{
				BrowseDir.BrowseDir_function(argv[1], argv[2], argv[3], argv[4], g_FILE_NAME);
			}
			// ��Ҫ���ܺ���ʵ�� - �����ļ���С
			if ((strcmp(argv[5], "-SIZE") == 0) ||
				(strcmp(argv[5], "-size") == 0))
			{
				BrowseDir.BrowseDir_function(argv[1], argv[2], argv[3], argv[4], g_FILE_SIZE);
			}
			// ��Ҫ���ܺ���ʵ�� - �����ļ�HASH
			if ((strcmp(argv[5], "-HASH") == 0) ||
				(strcmp(argv[5], "-hash") == 0))
			{
				BrowseDir.BrowseDir_function(argv[1], argv[2], argv[3], argv[4], 4);
			}
		}

		return 0;
	} 
	
	
	
	// �Աȹ���
	if ((strcmp(argv[1], "-Diff") == 0) ||
		(strcmp(argv[1], "-diff") == 0))
	{


		//�жϵڶ����������Ƿ�Ϊ��������
		if ((strcmp(argv[3], "-Rule") == 0) ||
			(strcmp(argv[3], "-rule") == 0)) 
		{
			//��������
			system("cls");
			//���˼·��
			//  0.�ļ��Ƿ����
			DiffRule.DiffRuleProcess(argv[2], argv[4]);
		}


	} 


	// ����ָ��MD5���ļ���ָ�����ļ���
	
	if (0 == strcmp("-C", argv[1]))
	{			

        if (argc !=6)
		{
			// ��ȡ�ı��ļ���vector��������·����
		    CopyfFile.ReadTXTFile_GetPath(argv[2], argv[4]);
		}




		// ָ����Ŀ¼
	}
	else
	{
		system("cls");
		usage();
		printf("��������ȷ������\n");
		return 0;
	}

	return 0;

}