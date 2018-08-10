#include <windows.h>
#include <iostream>
using namespace std;


// 互斥量是指线程1进行公共资源后不允许其他线程进入。
// 本示例利用互斥量实现线程间的同步。

HANDLE hMutex;//互斥量
int i = 1;//公共资源

DWORD WINAPI ThreadProc1(LPVOID lpParameter)//线程1
{
	while(true)
	{
		WaitForSingleObject(hMutex,INFINITE);
		if(i<5)
		{
			cout<<"线程hThread1当前访问的i值："<<i<<endl;
			i*=2;//每次乘以2
		}
		else
			break;//退出
		ReleaseMutex(hMutex);//释放互斥对象的所有权
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)//线程2
{
	while(true)
	{
		WaitForSingleObject(hMutex,INFINITE);
		if(i<50)
		{
			cout<<"线程hThread2当前访问的i值："<<i<<endl;
			i*=2;//每次乘以2
		}
		else 
			break;//退出
		ReleaseMutex(hMutex);//释放互斥对象的所有权
	}
	return 0;
}
void main()
{
	cout<<"-------互斥量实现线程同步--------"<<endl;
	hMutex = CreateMutex(NULL,false,NULL);//创建互斥量
	HANDLE hThread1;//定义线程1句柄
	HANDLE hThread2;//定义句柄
	hThread1=CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
	hThread2=CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);//创建线程
	CloseHandle(hThread1);//关闭线程1句柄
	CloseHandle(hThread2);//关闭线程2句柄
	WaitForSingleObject(hMutex,INFINITE);//等待互斥量状态
	ReleaseMutex(hMutex);//释放互斥量
	Sleep(4000);	
	cout<<"主线程正在运行"<<endl;	
}