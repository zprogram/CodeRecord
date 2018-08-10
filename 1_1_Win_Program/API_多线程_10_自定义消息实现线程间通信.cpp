#include <windows.h>
#include <iostream>
using namespace std;

#define WC_IDLE WM_USER+1//空闲
#define WC_BUSY WM_USER+2//繁忙

DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	DWORD dwThreadId = *(DWORD*)lpParameter;//线程ID
	while(true)
	{
		Sleep(1000);
		PostThreadMessage(dwThreadId,WC_IDLE,0,0);//每隔1秒发送空闲消息
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	DWORD dwThreadId = *(DWORD*)lpParameter;//线程ID
	while(true)
	{
		Sleep(1000);
		PostThreadMessage(dwThreadId,WC_BUSY,0,0);//每隔1秒发送繁忙消息
	}
	return 0;
}
void main()
{
	int i=1;//变量
	cout<<"变量i的初始值为："<<i<<endl;
	DWORD dwValue = GetCurrentThreadId();//获取当前线程ID
	HANDLE hThread1;//定义句柄
	HANDLE hThread2;//定义句柄
	hThread1=CreateThread(NULL,0,ThreadProc1,&dwValue,0,NULL);
	hThread2=CreateThread(NULL,0,ThreadProc2,&dwValue,0,NULL);//创建线程
	CloseHandle(hThread1);//关闭线程句柄
	CloseHandle(hThread2);//关闭线程句柄
	MSG msg;//消息变量
	while(GetMessage(&msg,NULL,0,0))//获取消息循环
	{
		switch(msg.message)
		{
		case WC_IDLE:
			i*=2;
			cout<<"当前线程空闲，实现i的乘2运算，其值="<<i<<endl;
			Sleep(5000);//允许用5分钟
			break;
		case WC_BUSY:
			cout<<"当前线程繁忙，不能对i进行乘2运算"<<endl;
			Sleep(1000);//再等待1秒
			break;
		default:
			cout<<"获取不知名的消息"<<msg.message<<endl;
			break;
		}
		Sleep(1000);//每隔1秒获取一次消息
	}
	cout<<"主线程完成"<<endl;
}