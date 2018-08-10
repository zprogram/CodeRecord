#pragma once
#include <stdlib.h>
#include <corecrt_io.h>


//���ַ�ת��Ϊ���ַ�(unicode -- > ascll)
#define WCHAR_TO_CHAR(lpW_Char,lpChar) WideCharToMultiByte(CP_ACP,NULL,lpW_Char,-1,lpChar,_countof(lpChar),NULL,FALSE);

//���ַ�ת��Ϊ���ַ�(unicode -- > ascll)
#define CHAR_TO_WCHAR(lpChar,lpW_Char) MultiByteToWideChar(CP_ACP,NULL,lpChar,-1,lpW_Char,_countof(lpW_Char));


class CBrowseDir
{
protected:
	//��ų�ʼĿ¼�ľ���·������'\'��β
	char m_szInitDir[_MAX_PATH];
	//������ļ���
	char *m_Outfile;


	//�ļ��ṹ��Ϣ
	_finddata_t fileinfo;


	//-size=1 -hash=2 -name=0
	int m_Option;


	int m_nFileCount;   	//�����ļ�����

	int m_nSubdirCount; 	//������Ŀ¼����


public:

	// ��ֵ��m_option��0���ļ��� 1���ļ���С��2��hash
	bool setValueOption(int nMode);

	//ȱʡ������
	CBrowseDir();

	//���ó�ʼĿ¼Ϊdir���������false����ʾĿ¼������
	bool SetInitDir(const char *dir);

	//���ó�ʼ������ļ�
	bool SetInitOutFile(const char *dir);


	//��ʼ������ʼĿ¼������Ŀ¼����filespecָ�����͵��ļ�
	//filespec����ʹ��ͨ��� * ?�����ܰ���·����
	//�������false����ʾ�������̱��û���ֹ
	bool BeginBrowse();

	//�����ļ�����
	int GetFileCount();
	// ����,ƥ������ģʽ
	int BrowseDir_function(char *Para1, char *Para2, char *Para3, char *Para4, int nMode);
	//������Ŀ¼����
	int GetSubdirCount();


	//����Ŀ¼
	void FindAllFile(const TCHAR* pszPath);

protected:

	//����BrowseDirÿ�ҵ�һ���ļ�,�͵���ProcessFile
	//�����ļ�����Ϊ�������ݹ�ȥ
	//�������false,��ʾ��ֹ�����ļ�
	//�û����Ը�д�ú���,�����Լ��Ĵ������
	//��д�麯��ProcessFile��ÿ����һ�Σ��ļ�������1
	 bool ProcessFile(const char *filename, unsigned long filesize );


};
