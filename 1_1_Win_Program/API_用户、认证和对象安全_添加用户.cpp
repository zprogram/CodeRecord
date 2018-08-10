// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

//Code by Pnig0s1992  
//Date:2012,3,17  
#include "stdafx.h"
#include <stdio.h>  
#include <Windows.h>  
#include <lm.h>  

#pragma comment(lib,"Netapi32.lib")  

int AddUser(LPWSTR lpUsername, LPWSTR lpPassword, LPWSTR lpServerName);
int SetGroup(LPWSTR lpUsername, LPWSTR lpServerName, LPCWSTR lpGroupName);
BOOL ImprovePriv(LPCWSTR name);

int main(INT argc, char * argv[])
{
	BOOL bResult = ImprovePriv(SE_MACHINE_ACCOUNT_NAME);
	if (argc < 3)
	{
		printf("\nCode by Pnig0s1992");
		printf("\nUsage:");
		printf("\n\t%s UserName Password", argv[0]);
		printf("\n\tRemark:Default add to Group:Administrators.");
		return -1;
	}
	if (bResult)
	{
		printf("Successfully promote priv!");
	}
	else
	{
		printf("Failed promote priv.");
		return -1;
	}
	int Namesize = MultiByteToWideChar(CP_ACP, 0, argv[1], -1, NULL, 0);
	wchar_t *wUserName = new wchar_t[Namesize + 1];
	if (!MultiByteToWideChar(CP_ACP, 0, argv[1], -1, wUserName, Namesize))
	{
		return false;
	}
	int Passsize = MultiByteToWideChar(CP_ACP, 0, argv[2], -1, NULL, 0);
	wchar_t *wPassword = new wchar_t[Passsize + 1];
	if (!MultiByteToWideChar(CP_ACP, 0, argv[2], -1, wPassword, Passsize))
	{
		return false;
	}
	LPWSTR lpName = wUserName;
	LPWSTR lpPassword = wPassword;
	LPWSTR lpSevName = NULL;
	LPCWSTR lpGroupName = L"Administrators";
	AddUser(lpName, lpPassword, lpSevName);
	SetGroup(lpName, lpSevName, lpGroupName);
	return 0;
}

BOOL ImprovePriv(LPCWSTR name)
{
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	{
		printf("\nGet process token failed.(%d)", GetLastError());
		return FALSE;
	}
	TOKEN_PRIVILEGES tkp;
	tkp.PrivilegeCount = 1;
	if (!LookupPrivilegeValue(NULL, name, &tkp.Privileges[0].Luid))
	{
		printf("\nLookup process priv failed.(%d)", GetLastError());
		return FALSE;
	}
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL))
	{
		printf("\nAjust process priv failed.(%d)", GetLastError());
		return FALSE;
	}
	CloseHandle(hToken);
	return TRUE;
}

int AddUser(LPWSTR lpUsername, LPWSTR lpPassword, LPWSTR lpServerName)
{
	USER_INFO_1 ui;
	DWORD dwLevel = 1;
	DWORD dwError = 0;
	NET_API_STATUS nStatus;
	ui.usri1_name = lpUsername;
	ui.usri1_password = lpPassword;
	ui.usri1_priv = USER_PRIV_USER;
	ui.usri1_home_dir = NULL;
	ui.usri1_comment = NULL;
	ui.usri1_flags = UF_SCRIPT;
	ui.usri1_script_path = NULL;
	nStatus = NetUserAdd(lpServerName, dwLevel, (LPBYTE)&ui, &dwError);
	if (nStatus == NERR_Success)
	{
		printf("\nAdd user:%S successfully!", lpUsername);
	}
	else
	{
		printf("\nAdd user failed:%d.", nStatus);
	}
	return 0;
}

int SetGroup(LPWSTR lpUsername, LPWSTR lpServerName, LPCWSTR lpGroupName)
{
	NET_API_STATUS nStatus;
	LOCALGROUP_MEMBERS_INFO_3  lgui;
	lgui.lgrmi3_domainandname = lpUsername;
	nStatus = NetLocalGroupAddMembers(lpServerName, lpGroupName, 3, (LPBYTE)&lgui, 1);

	if (nStatus == NERR_Success)
	{
		printf("\nSuccessfully set USER:%S to GROUP:%S!", lpUsername, lpGroupName);
	}
	else if (nStatus == NERR_GroupNotFound)
	{
		printf("\nCan't find such a group:%S.", lpGroupName);
	}
	else
	{
		printf("\nSet GROUP:%S failed.", lpGroupName);
	}
	return 0;
}
