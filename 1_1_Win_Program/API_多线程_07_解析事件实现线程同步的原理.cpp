#include <windows.h>
#include <iostream>
using namespace std;

// 解析事件实现线程同步的原理
// 当线程1已满足继续访问i值时，线程2不能访问i。
// 原因是线程1在break后处于无限循环，线程2根本没机会访问变量i


int i = 1;//全局变量
HANDLE hEvent;//事件
bool th1_flag=true;//线程1
bool th2_flag=true;//线程2
DWORD WINAPI ThreadProc1(LPVOID lpParameter)//线程1
{
	while(th1_flag)
	{
		WaitForSingleObject(hEvent,INFINITE);
		cout<<"进入线程1。。。"<<endl;
		if(i<5)//界值5
		{
			cout<<"线程hThread1当前访问的i值："<<i<<endl;
			i*=2;//每次乘以2
		}
		else
			th1_flag=false;
		SetEvent(hEvent);
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)//线程2
{
	while(th2_flag)
	{
		WaitForSingleObject(hEvent,INFINITE);
		cout<<"进入线程2。。。"<<endl;
		if(i<20)//界值20
		{
			cout<<"线程hThread2当前访问的i值："<<i<<endl;
			i*=2;//每次乘以2
		}
		else
			th2_flag=false;
		SetEvent(hEvent);
	}
	return 0;
}
void main()
{
	cout<<"-------事件实现线程同步原理--------"<<endl;
	HANDLE hThread1;//定义句柄
	HANDLE hThread2;//定义句柄
	hThread1 = CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
	hThread2 = CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);//创建线程
	CloseHandle(hThread1);//关闭线程2
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