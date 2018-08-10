#include <windows.h>
#include <iostream>
using namespace std;

// 利用事件使线程1和线程2同步访问公共资源，以使每个线程都能得到更新后的公共资源状态。
// 利用两个线程依次获取当前全局变量的值。利用两个线程依次获取当前全局变量的值。

int i = 1;//全局变量
HANDLE hEvent;//事件

DWORD WINAPI ThreadProc1(LPVOID lpParameter)//线程1
{
	while(true)
	{
		WaitForSingleObject(hEvent,INFINITE);
		if(i<5)//界值5
		{
			cout<<"线程hThread1当前访问的i值："<<i<<endl;
			i*=2;//每次乘以2
		}
		else
			break;//退出
		SetEvent(hEvent);
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)//线程2
{
	while(true)
	{
		WaitForSingleObject(hEvent,INFINITE);
		if(i<20)//界值20
		{
			cout<<"线程hThread2当前访问的i值："<<i<<endl;
			i*=2;//每次乘以2
		}
		else 
			break;//退出
		SetEvent(hEvent);
	}
	return 0;
}
void main()
{
	cout<<"-------事件实现线程同步--------"<<endl;
	HANDLE hThread1;//定义句柄
	HANDLE hThread2;//定义句柄
	hThread1 = CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
	hThread2 = CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);//创建线程
	CloseHandle(hThread1);//关闭线程1
	CloseHandle(hThread2);//关闭线程2
	hEvent = CreateEvent(NULL,false,false,NULL);//创建事件
	if(hEvent)
	{
		if(GetLastError() == ERROR_ALREADY_EXISTS)//创建事件有错
		{
			cout<<"该事件已经存在!"<<endl;
			return;
		}
	}
	SetEvent(hEvent);//设置事件
	Sleep(4000);
	CloseHandle(hEvent);//关闭事件句柄
}