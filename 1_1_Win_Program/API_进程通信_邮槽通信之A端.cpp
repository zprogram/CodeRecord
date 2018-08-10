#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hMailslot;//邮槽句柄
void main()
{
	hMailslot = CreateMailslot(TEXT("\\\\.\\mailslot\\slot"),0,
		MAILSLOT_WAIT_FOREVER,NULL);//创建邮槽
	if(hMailslot==INVALID_HANDLE_VALUE)
	{
		cout<<"创建邮槽失败。。。"<<endl;
		return;
	}
	char buffer[100];//缓冲区
	DWORD dwRead;
	if(!ReadFile(hMailslot,buffer,100,&dwRead,NULL))//读取数据
	{
		cout<<"通过邮槽读取数据失败。。。"<<endl;
		return;
	}
	cout<<"通过邮槽读取数据成功："<<buffer<<endl;//输出 
	CloseHandle(hMailslot);//关闭句柄
}