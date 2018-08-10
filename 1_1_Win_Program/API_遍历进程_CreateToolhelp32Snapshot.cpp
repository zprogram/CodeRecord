// 20171102-遍历进程.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdafx.h"
#include "windows.h"
#include "locale.h"
#include <tlhelp32.h>


//本程序演示CreateToolhelp32Snapshot Process32First Process32Next


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "chs");//置本地语言环境
	PROCESSENTRY32 pe32;//进程结信息结构体
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"CreateToolhelp32Snapshot 调用失败.\n");
		return -1;
	}
	BOOL bMore = Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		wprintf_s(L"进程名称：%s\n", pe32.szExeFile);
		wprintf_s(L"进程ID：%u\n\n", pe32.th32ProcessID);
		bMore = Process32Next(hProcessSnap, &pe32);
	}
	CloseHandle(hProcessSnap);
	getchar();
	return 0;
}


