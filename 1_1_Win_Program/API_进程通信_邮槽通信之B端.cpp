#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hMailslot;//邮槽句柄
void main()
{
	hMailslot = CreateFile(TEXT("\\\\.\\mailslot\\slot"),GENERIC_WRITE,
		FILE_SHARE_READ,NULL,OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,NULL);//打开邮槽
	if(hMailslot==INVALID_HANDLE_VALUE)
	{
		cout<<"打开邮槽失败。。。"<<endl;
		return;//返回
	}
	DWORD dwWrite;   
	char* buffer = "申请访问A端";   
	if(!WriteFile(hMailslot, buffer, strlen(buffer)+1, &dwWrite, NULL))  //写入数据
	{        
		cout<<"通过邮槽写入数据失败。。。"<<endl;    
		return;
	}  
	cout<<"通过邮槽写入数据成功："<<buffer<<endl;
}