#include <windows.h>
#include <iostream>
using namespace std;

// 线程的运行有先有后，本示例模拟设置线程的优先级。
// 如遇线程1比线程2的优先级高，就让线程1先执行，线程2后执行。
// 


HANDLE hThread1;								//定义句柄
HANDLE hThread2;								//定义句柄
DWORD WINAPI ThreadProc1(LPVOID lpParameter)//线程1
{
	while(true)
	{
		cout<<"进入线程1。。。"<<endl;
		Sleep(1000);
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)//线程2
{
	while(true)
	{
		cout<<"进入线程2。。。"<<endl;
		Sleep(1000);
	}
	return 0;
}
void main()
{
	hThread1 = CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
	SetThreadPriority(hThread1,THREAD_PRIORITY_IDLE);		//设置优先级空闲
	hThread2 = CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);
	SetThreadPriority(hThread2,THREAD_PRIORITY_HIGHEST);	//最高
	Sleep(5000);							//睡一会儿
	CloseHandle(hThread1);					//关闭线程句柄
	CloseHandle(hThread2);					//关闭线程句柄
	cout<<"主线程正在运行"<<endl;
}