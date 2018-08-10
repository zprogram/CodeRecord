#include "stdafx.h"
#include "BrowseDir.h"
#include <direct.h>
#include <string.h>
#include <io.h>
#include "iostream"
#include <Windows.h>
#include "Md5.h"
using namespace std;




/************************************
* Access:    public 
* ��������:  setValueOption
* ��������:  ����ѡ������

* �����б�:
*   char * nPara:
*   $
* ����ֵ:    bool
* 
*************************************/

bool CBrowseDir::setValueOption(int nMode)
{
	// ����ģʽ��-ֵ
	m_Option = nMode;

	return false;
}

CBrowseDir::CBrowseDir()
{
	//�õ�ǰĿ¼��ʼ��m_szInitDir
	_getcwd(m_szInitDir, _MAX_PATH);

	//��ʼ�����ݳ�Աm_nFileCount��m_nSubdirCount
	m_nFileCount = m_nSubdirCount = 0;

	//���Ŀ¼�����һ����ĸ����'\',����������һ��'\'
	int len = strlen(m_szInitDir);
	if (m_szInitDir[len - 1] != '\\')
		strcat_s(m_szInitDir, "\\");
}

/************************************
* Access:    public 
* ��������:  SetInitOutFile
* ��������:  ɾ�����ڵ�����ļ�

* �����б�:
*   const char * dir:
*   $
* ����ֵ:    bool
* 
*************************************/

bool CBrowseDir::SetInitOutFile(const char * dir)
{

	//ָ��const��ָ�벻�ܱ�����ָ���const��ָ��
	//���һ���ڴ棬���ַ����ƹ�ȥ
	m_Outfile = new char[strlen(dir) + 1];
	strcpy(m_Outfile, dir);


	//char*תwchar*
	const size_t cSize = strlen(m_Outfile) + 1;
	wchar_t* m_wOutfile = new wchar_t[cSize];
	mbstowcs(m_wOutfile, m_Outfile, cSize);


	//ɾ��ԭ�ļ�
	DeleteFile(m_wOutfile);
	// �ļ������
	HANDLE pFile = CreateFile(m_wOutfile, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);

	if (pFile ==INVALID_HANDLE_VALUE)
	{
		printf("����ʧ��");
	}
	
	CloseHandle(pFile);



	return true;
}

/************************************
* Access:    public 
* ��������:  SetInitDir
* ��������:  ��ʼ��������Ŀ¼

* �����б�:
*   const char * dir:
*   $
* ����ֵ:    bool
* 
*************************************/

bool CBrowseDir::SetInitDir(const char *dir)
{
	//�Ȱ�dirת��Ϊ����·��
	if (_fullpath(m_szInitDir, dir, _MAX_PATH) == NULL)
		return false;

	//�ж�Ŀ¼�Ƿ����
	if (_chdir(m_szInitDir) != 0)
		return false;

	//���Ŀ¼�����һ����ĸ����'\',����������һ��'\'
	int len = strlen(m_szInitDir);
	if (m_szInitDir[len - 1] != '\\')
		strcat(m_szInitDir, "\\");

	return true;
}



void CBrowseDir::FindAllFile(const TCHAR * pszPath)
{
	WIN32_FIND_DATA stcFindData = { 0 };
	TCHAR szSeach[MAX_PATH];
	wchar_t buf[MAX_PATH];
	char filename[MAX_PATH];
	wsprintf(szSeach, L"%s\\*", pszPath);
	HANDLE hFind = FindFirstFile(szSeach ,
								 &stcFindData);

	do
	{
		// �жϵ�ǰ�ҵ����ļ��Ƿ��ǵ�ǰ���ϲ�Ŀ¼
		if(wcscmp(stcFindData.cFileName , L".") == 0
		   ||
		   wcscmp(stcFindData.cFileName , L"..") == 0)
		{
			// ���������֮һ,�ͽ�������ѭ��
			continue;
		}
		
		m_nFileCount++;
		//wprintf(L"%s\\%s\n" ,pszPath,stcFindData.cFileName);
		swprintf_s(buf, 100, L"%s%s", pszPath, stcFindData.cFileName);
		WCHAR_TO_CHAR(buf, filename)
		ProcessFile(filename, stcFindData.nFileSizeLow); //�����ļ��������ļ������ļ���С

		// �ж��ļ��Ƿ���Ŀ¼
		if(stcFindData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)
		{
			//Ŀ¼������
			m_nSubdirCount++;
			TCHAR path[ MAX_PATH ];
			swprintf_s(path , L"%s\\%s" , pszPath , stcFindData.cFileName);
			FindAllFile(path);
		}

	} 
	while(FindNextFile(hFind , &stcFindData));

}

bool CBrowseDir::BeginBrowse()
{
	setlocale(LC_ALL, "chs");
	TCHAR  WszInitDir[MAX_PATH];
	CHAR_TO_WCHAR(m_szInitDir, WszInitDir)
	FindAllFile(WszInitDir);
	return true;
}







/************************************
* Access:    virtual protected 
* ��������:  ProcessFile
* ��������:

* �����б�:
*   const char * filename:�ļ���
*   $
* ����ֵ:    bool
* 
*************************************/

bool CBrowseDir::ProcessFile(const char *filename, unsigned long file_size)
{
	//char*תwchar*
	const size_t cSize = strlen(m_Outfile) + 1;
	wchar_t* m_wOutfile = new wchar_t[cSize];
	mbstowcs(m_wOutfile, m_Outfile, cSize);
	//�������ļ�
	HANDLE pFile = CreateFile(m_wOutfile, GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,  //�ļ�����
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	//�ƶ����ļ�β��
	SetFilePointer(pFile, 0, 0, FILE_END);
	DWORD fileSize;

	//���ٶѿռ䣬���Ǽ��ļ���С���ļ�hash�����
	char * filename_str = new char[strlen(filename)+60];

	//�ж�д���Ƿ�ɹ�
	BOOL bRet; 

    //�������ģʽ�ж�ѡ���������
	switch (m_Option)
	{
		// �ļ���С
	    case g_FILE_SIZE: 
	    {
		   //����ļ���+�ļ���С
		   cout << filename<<"_"<<file_size << endl;
		   sprintf(filename_str, "%s_%d\r\n", filename, file_size);
		   bRet = WriteFile(pFile, filename_str, strlen(filename_str), &fileSize, NULL);

	    }
		break;

		// �ļ�hash
		case g_FILE_HASH:
		{

			//�õ�MD5ֵ
			char * Md5Value = md5FileValue((char*)filename);
			//�����ǰ��ֵ
			cout << filename << "_" << Md5Value << endl;
			sprintf(filename_str, "%s_%s\r\n", filename, Md5Value);
			bRet = WriteFile(pFile, filename_str, strlen(filename_str), &fileSize, NULL);


		}
		break;

		// �ļ���С+HASH
		case 4:
		{
			//�õ�MD5ֵ
			char * Md5Value = md5FileValue((char*)filename);
			//�����ǰ��ֵ
			cout << filename << "_" << file_size << "_" <<  Md5Value << endl;
			sprintf(filename_str, "%s_%d_%s\r\n", filename, file_size,Md5Value);
			bRet = WriteFile(pFile, filename_str, strlen(filename_str), &fileSize, NULL);


		}
		break;

		// Ĭ�������ֻ����ļ���
		default:
		{
			//����ļ���
			cout << filename << endl;
			sprintf(filename_str, "%s\r\n", filename);
			bRet = WriteFile(pFile, filename_str, strlen(filename_str), &fileSize, NULL);
		}
		break;
	}


	// ���������Ϣ
	if (bRet)
	{
        //���д����ļ�
		WCHAR test[260];
		CHAR_TO_WCHAR(filename_str,test);
		//���������Ϣ
		OutputDebugString(test);
		OutputDebugString(TEXT("WriteFile д�ļ��ɹ�\r\n"));
	}

	//�õı���ϰ���ǿ���ˮ��ͷ��Ҫ�ص�ˮ��ͷ
	delete[] filename_str;
	CloseHandle(pFile);

	return true;
}





int CBrowseDir::GetFileCount()
{
	return m_nFileCount;
}





/************************************
* Access:    public
* ��������:  FunctionMain
* ��������:

* �����б�:
*   char * Para1:����1
*   char * Para2:�Ѽ�����·��
*   char * Para3:����2
*   char * Para4:ƥ����ı�·��
*   char * Para5:��������� 0 name 1 size 2 hash
*   $
* ����ֵ:    int
*
*************************************/

int CBrowseDir::BrowseDir_function(char * Para1, char * Para2, char * Para3, char * Para4, int nMode)
{

	//�������ģʽ 0���ļ��� 1���ļ���С��2��hash
	setValueOption(nMode);



	//����Ҫ������Ŀ¼
	if (!SetInitDir(Para2))
	{
		puts("Ŀ¼�����ڡ�");
		return 0;
	}


	//�ж��������ļ��Ƿ��Ѿ����ɹ���������ɾ��
	SetInitOutFile(Para4);

	//��ʼ����
	BeginBrowse();
	printf("\n�ļ�����: %d\n��Ŀ¼����:%d\n", GetFileCount(), GetSubdirCount());
	system("pause");

	return 0;

}

//������Ŀ¼����
int CBrowseDir::GetSubdirCount()
{
	//��Ϊ�����ʼĿ¼ʱ��Ҳ����ú���ProcessDir��
	//���Լ�1�������������Ŀ¼������
	return m_nSubdirCount;
}


