// 20180218_ע����̻���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>

int main()
{
        //ִ�г���
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;

	bool fRet = CreateProcess(_T("C:\\Windows\\System32\\cmd.exe"), _T("/c net user"), NULL, FALSE, NULL, NULL, NULL, NULL, &si, &pi);
	return 0;
}