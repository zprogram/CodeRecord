#include "stdafx.h"
#include "CopyFileToDir.h"
#include <fstream>  
#include <string>  
#include <iostream>  
#include <windows.h>


//���ַ�ת��Ϊ���ַ�(unicode -- > ascll)
#define WCHAR_TO_CHAR(lpW_Char,lpChar) WideCharToMultiByte(CP_ACP,NULL,lpW_Char,-1,lpChar,_countof(lpChar),NULL,FALSE);

//���ַ�ת��Ϊ���ַ�(unicode -- > ascll)
#define CHAR_TO_WCHAR(lpChar,lpW_Char) MultiByteToWideChar(CP_ACP,NULL,lpChar,-1,lpW_Char,_countof(lpW_Char));

using namespace std;

CopyFileToDir::CopyFileToDir()
{
}

bool CopyFileToDir::ReadTXTFile_GetPath(char * PathText,char *Path)
{

	//���ļ�
	ifstream in(PathText);
	string filename;
	string line;

	//�����ļ�����
	int num = 0;

	if (in) // �и��ļ�  
	{
		while (getline(in, line)) // line�в�����ÿ�еĻ��з�  
		{
			//��ȡ�ı����ݵ�vector��
			vecTatgetPath.push_back(line);
			num++;

		}
	}
	else // û�и��ļ�  
	{
		cout << "no such file" << endl;
	}
	cout << "�Ա��ļ�����Ϊ" << num << endl;


	WCHAR  W_Dir[MAX_PATH];
	WCHAR W_FilePath[MAX_PATH];
	WCHAR W_FileName[MAX_PATH];



	for (size_t i = 0; i < vecTatgetPath.size(); i++)
	{

		CHAR_TO_WCHAR(Path, W_Dir);
		CHAR_TO_WCHAR(vecTatgetPath[i].c_str(), W_FilePath);
		//ȡ�ļ���
		size_t found = vecTatgetPath[i].find_last_of("/\\");
		CHAR_TO_WCHAR(vecTatgetPath[i].substr(found).c_str(), W_FileName);
		lstrcat(W_Dir,W_FileName);

		if (!CopyFile(W_FilePath, W_Dir, TRUE))
		{
			//LastError == 0x50���ļ����ڡ�
			if (GetLastError() == 0x50)
			{
				printf("�ļ�%ls�Ѿ����ڣ��Ƿ񸲸ǣ�y/n��", W_Dir);
				if ('y' == getchar())
				{
					//���ƣ������Ѿ����ڵ��ļ���
					if (!CopyFile(W_FilePath, W_Dir, FALSE))
					{
						printf("�����ļ�����%d\n", GetLastError());
					}
					else
					{
						printf("���Ƴɹ���\n");
					}
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			printf("%ls ���Ƴɹ���\n", W_FileName);
		}

	}


	


	return false;


}


CopyFileToDir::~CopyFileToDir()
{
}
