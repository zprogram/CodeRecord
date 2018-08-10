#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hThread1;									//定义句柄
HANDLE hThread2;								//定义句柄
int i=1;//全局变量
bool flag1=true;
bool flag2=true;
DWORD WINAPI ThreadProc1(LPVOID lpParameter)//线程1
{
	while(flag1)
	{
		if(i<50)//界值5
		{
			cout<<"进入线程1。。。"<<endl;
			cout<<"线程hThread1当前访问的i值："<<i<<endl;
			if(i%2==0)
			{
				SuspendThread(hThread1);		//挂起自己
				cout<<"挂起线程1"<<endl;
			}
			i*=2;//每次乘以2
		}
		else
			flag1=false;
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)//线程2
{
	while(flag2)
	{
		if(i<100)//界值20
		{
			cout<<"进入线程2。。。"<<endl;
			cout<<"线程hThread2当前访问的i值："<<i<<endl;
			if(i%9==0)
			{
				ResumeThread(hThread1);		//恢复线程hThread1
				cout<<"恢复线程1"<<endl;
			}
			i*=3;//每次乘以3
		}
		else 
			flag2=false;
	}
	return 0;
}
void main()
{
	hThread1 = CreateThread(NULL,0,ThreadProc1,NULL,CREATE_SUSPENDED,NULL);
	ResumeThread(hThread1);								//恢复线程
	hThread2 = CreateThread(NULL,0,ThreadProc2,NULL,CREATE_SUSPENDED,NULL);
	ResumeThread(hThread2);
	Sleep(5000);							//睡一会儿
	CloseHandle(hThread1);					//关闭线程句柄
	CloseHandle(hThread2);					//关闭线程句柄
	cout<<"主线程正在运行"<<endl;
}