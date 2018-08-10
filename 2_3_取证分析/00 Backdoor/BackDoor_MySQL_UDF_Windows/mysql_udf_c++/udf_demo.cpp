#include <winsock.h>
#include <mysql.h>  

#include <stdio.h>
#include <Windows.h>

//--------
extern "C" __declspec(dllexport)my_bool regwrite_init(UDF_INIT *initid,
	UDF_ARGS *args,
	char *message)
{  

	//�жϲ����Ƿ���ȷ,���������������ַ���
	if (args->arg_type[0] == STRING_RESULT &&  // ����
		args->arg_type[1] == STRING_RESULT &&  // ����
		args->arg_type[2] == STRING_RESULT &&  // ��
		args->arg_type[3] == STRING_RESULT     // д���ֵ
		)
	{
		return 0;
	}
	else {
		strcpy(
			message
			, "Expected exactly four string type parameter"
			);
		return 1;
	}
}
extern "C" __declspec(dllexport)char*  regwrite(UDF_INIT *initid
	, UDF_ARGS *args
	, char* result
	, unsigned long* length
	, char *is_null
	, char *error)
{

	HKEY hRoot;
	// �жϸ���
	if (strcmp("HKEY_LOCAL_MACHINE", (char*)(args->args)[0]) == 0)
		hRoot = HKEY_LOCAL_MACHINE;
	else if (strcmp("HKEY_CLASSES_ROOT", (char*)(args->args)[0]) == 0)
		hRoot = HKEY_CLASSES_ROOT;
	else if (strcmp("HKEY_CURRENT_USER", (char*)(args->args)[0]) == 0)
		hRoot = HKEY_CURRENT_USER;
	else if (strcmp("HKEY_USERS", (char*)(args->args)[0]) == 0)
		hRoot = HKEY_USERS;
	else
	{
		initid->ptr = (char *)malloc(50 + strlen((args->args)[0]));
		sprintf(initid->ptr, "unknow:%s\r\n", (args->args)[0]);
		*length = (unsigned long)strlen(initid->ptr);
		return initid->ptr;
	}

	HKEY hKey;
	DWORD dwType = REG_SZ;
	// ��ע�������������򴴽���

	// �жϸ����治����
	// szSubKey����ת�� charתwchar
	int szSubKey_len = (int)MultiByteToWideChar(CP_ACP, 0, (args->args)[1], strlen((args->args)[1]), NULL, 0);
	wchar_t*    szSubKey = new wchar_t[szSubKey_len + 1];
	MultiByteToWideChar(CP_ACP, 0, (args->args)[1], strlen((args->args)[1]), szSubKey, szSubKey_len);
	szSubKey[szSubKey_len] = '\0';

	size_t lRet = RegCreateKeyEx(hRoot, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (lRet != ERROR_SUCCESS)
	{
		initid->ptr = (char *)malloc(50 + strlen((args->args)[1]));
		sprintf(initid->ptr, "unknow:%s\r\n", (args->args)[1]);
		*length = (unsigned long)strlen(initid->ptr);
		return initid->ptr;
	}

	// �޸�ע����ֵ��û���򴴽���
	// ValueName�޸ĵļ���ת�� charתwchar
	int ValueName_len = MultiByteToWideChar(CP_ACP, 0, (args->args)[2], strlen((args->args)[2]), NULL, 0);
	wchar_t*   ValueName = new wchar_t[ValueName_len + 1];
	MultiByteToWideChar(CP_ACP, 0, (args->args)[2], strlen((args->args)[2]), ValueName, ValueName_len);
	ValueName[ValueName_len] = '\0';

	//// ע����ֵ����ת�� charתwchar
	int data_len = MultiByteToWideChar(CP_ACP, 0, (args->args)[3], strlen((args->args)[3]), NULL, 0);
	wchar_t*  data = new wchar_t[data_len + 1];
	MultiByteToWideChar(CP_ACP, 0, (args->args)[3], strlen((args->args)[3]), data, data_len);
	data[data_len] = '\0';
	// ������ֽڵĳ���
	DWORD iLen = (DWORD)wcslen(data);

	//ע����ֵ�޸�
	lRet = RegSetValueEx(hKey, ValueName, 0, dwType, (unsigned char*)data, sizeof(wchar_t)*data_len);
	if (lRet != ERROR_SUCCESS)
	{
		initid->ptr = (char *)malloc(50 + strlen((args->args)[2]));
		sprintf(initid->ptr, "unknow:%s\r\n", (args->args)[2]);
		*length = (unsigned long)strlen(initid->ptr);
		return initid->ptr;
	}
	RegCloseKey(hKey);


	// ��*is_null������Ϊ1ʱ������ֵΪNULL
	if (!(*result) || result == NULL) {
		*is_null = 1;

	}
	else {
		sprintf(result, "success");
		result[iLen] = 0x00;
		*length = strlen(result);
	}
	// ���ؽ��
	return result;
}
extern "C" __declspec(dllexport)void regwrite_deinit(
	UDF_INIT *initid)
{

	if (initid->ptr)
	{
		free(initid->ptr);
	}
}