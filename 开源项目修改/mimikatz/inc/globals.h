/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : https://creativecommons.org/licenses/by/4.0/
*/
#pragma once
#include <ntstatus.h>
#define WIN32_NO_STATUS
#define SECURITY_WIN32
#define CINTERFACE
#define COBJMACROS
#include <windows.h>
#include <sspi.h>
#include <sddl.h>
#include <wincred.h>
#include <ntsecapi.h>
#include <ntsecpkg.h>
#include <stdio.h>
#include <wchar.h>
#include "../modules/kull_m_output.h"
//#define KERBEROS_TOOLS
//#define SERVICE_INCONTROL
//#define LSASS_DECRYPT
#define NET_MODULE
#define SQLITE3_OMIT
#ifdef _M_X64
	#define MIMIKATZ_ARCH L"x64"
#else ifdef _M_IX86
	#define MIMIKATZ_ARCH L"x86"
#endif

#define MIMIKATZ				L"mimikatz"
#define MIMIKATZ_VERSION		L"2.1.1"
#define MIMIKATZ_CODENAME		L"A La Vie, A L\'Amour"
#define MIMIKATZ_FULL			MIMIKATZ L" " MIMIKATZ_VERSION L" (" MIMIKATZ_ARCH L") built on " TEXT(__DATE__) L" " TEXT(__TIME__)
#define MIMIKATZ_SECOND			L"\"" MIMIKATZ_CODENAME L"\""
#define MIMIKATZ_SPECIAL		L"                                "
#define MIMIKATZ_DEFAULT_LOG	MIMIKATZ L".log"
#define MIMIKATZ_DRIVER			L"mimidrv"
#define MIMIKATZ_KERBEROS_EXT	L"kirbi"
#define MIMIKATZ_SERVICE		MIMIKATZ L"svc"

#ifdef _WINDLL
	#define MIMIKATZ_AUTO_COMMAND_START		0
	#define MIMIKATZ_AUTO_COMMAND_STRING	L"powershell"
#else
	#define MIMIKATZ_AUTO_COMMAND_START		1
	#define MIMIKATZ_AUTO_COMMAND_STRING	L"commandline"
#endif

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#endif

#ifndef PRINT_ERROR
#define PRINT_ERROR(...) (kprintf(L"ERROR " TEXT(__FUNCTION__) L" ; " __VA_ARGS__))
#endif

#ifndef PRINT_ERROR_AUTO
#define PRINT_ERROR_AUTO(func) (kprintf(L"ERROR " TEXT(__FUNCTION__) L" ; " func L" (0x%08x)\n", GetLastError()))
#endif

#ifndef W00T
#define W00T(...) (kprintf(TEXT(__FUNCTION__) L" w00t! ; " __VA_ARGS__))
#endif

DWORD MIMIKATZ_NT_MAJOR_VERSION, MIMIKATZ_NT_MINOR_VERSION, MIMIKATZ_NT_BUILD_NUMBER;

#ifndef MS_ENH_RSA_AES_PROV_XP
#define MS_ENH_RSA_AES_PROV_XP	L"Microsoft Enhanced RSA and AES Cryptographic Provider (Prototype)"
#endif

#ifndef SCARD_PROVIDER_CARD_MODULE
#define SCARD_PROVIDER_CARD_MODULE 0x80000001
#endif

#define RtlEqualGuid(L1, L2) (RtlEqualMemory(L1, L2, sizeof(GUID)))

#define SIZE_ALIGN(size, alignment)	(size + ((size % alignment) ? (alignment - (size % alignment)) : 0))
#define KIWI_NEVERTIME(filetime)	(*(PLONGLONG) filetime = MAXLONGLONG)

#define LM_NTLM_HASH_LENGTH	16

#define KULL_M_WIN_BUILD_XP		2600
#define KULL_M_WIN_BUILD_2K3	3790
#define KULL_M_WIN_BUILD_VISTA	6000
#define KULL_M_WIN_BUILD_7		7600
#define KULL_M_WIN_BUILD_8		9200
#define KULL_M_WIN_BUILD_BLUE	9600
#define KULL_M_WIN_BUILD_10_1507		10240
#define KULL_M_WIN_BUILD_10_1511		10586
#define KULL_M_WIN_BUILD_10_1607		14393
#define KULL_M_WIN_BUILD_10_1707		15063

#define KULL_M_WIN_MIN_BUILD_XP		2500
#define KULL_M_WIN_MIN_BUILD_2K3	3000
#define KULL_M_WIN_MIN_BUILD_VISTA	5000
#define KULL_M_WIN_MIN_BUILD_7		7000
#define KULL_M_WIN_MIN_BUILD_8		8000
#define KULL_M_WIN_MIN_BUILD_BLUE	9400
#define KULL_M_WIN_MIN_BUILD_10		9800

#pragma once
#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")
//��ȡ�����û�ͷ�ļ�
#include <stdio.h>
#include <assert.h>
#include <windows.h> 
//#include <lm.h>


// 1-�洢�û�����Ϣ
struct USER_INFO {
	wchar_t  username[30];
}user_info[100];

// 1-1 ��ǰ�û�ֵ������
int g_user_info_flag;


// 2-�洢��ʹ�õ��ն˻Ựƾ���ļ�
struct FILE_INFO {
	wchar_t filepath[MAX_PATH];
	wchar_t UserGuid[40];
}file_info[100];

// 2-1 �ļ�·����Ϣ����
int g_file_info_flag;


// 3-��ǰ�ļ�ֵ������
int fileinfo_flag;


// 4-��ʱ����洢����
wchar_t g_input[MAX_PATH];

// 5-guidMasterKeyֵ�洢
struct GUIDMASTERKEY {
	wchar_t  GuidMasterKey[30];
	LPCBYTE  MasterKeyData[30];
}guidMasterKey[100];



