#include <windows.h>
#include <iostream>
using namespace std;


// 利用信号量实现线程同步，在每次进出线程执行函数时拥有资源所有权、释放资源所有权。


bool idle = true;//标志资源是否可被访问
int i=1;//初始值
HANDLE hDemaphore;//信号量
bool th1_flag=true;//线程1标志
bool th2_flag=true;//线程2标志
DWORD WINAPI ThreadProc1(LPVOID lpParameter)//线程1
{
	while(th1_flag)
	{
		WaitForSingleObject(hDemaphore,INFINITE);
		cout<<"访问线程1。。。"<<endl;
		if(i<5)
		{
			if(idle)//空闲
			{
				cout<<"线程hThread1当前访问的i值："<<i<<endl;
				idle=false;//不可访问
				Sleep(1000);//使用期1秒
				idle=true;//可被访问
			}
			i*=2;
		}
		else
			th1_flag=false;
		ReleaseSemaphore(hDemaphore,1,NULL);//释放信号
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)//线程2
{
	while(th2_flag)
	{
		WaitForSingleObject(hDemaphore,INFINITE);
		if(i<20)
		{
			if(idle)//空闲
			{
				cout<<"线程hThread2当前访问的i值："<<i<<endl;
				idle=false;//不可访问
				Sleep(1000);//使用期1秒
				idle=true;//可被访问
			}
			i*=2;
		}
		else 
			th2_flag=false;
		ReleaseSemaphore(hDemaphore,1,NULL);//释放信号
	}
	return 0;
}
void main()
{
	cout<<"------信号量应用-------"<<endl;
	hDemaphore = CreateSemaphore(NULL,1,1,NULL);//信号量对象
	//hDemaphore = CreateSemaphore(NULL,2,3,NULL);//最大信号量为3个，但只能开通2个
	HANDLE hThread1;//定义句柄
	HANDLE hThread2;//定义句柄
	hThread1 = CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);
	hThread2 = CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);//创建线程
	CloseHandle(hThread1);//关闭线程句柄
	CloseHandle(hThread2);
	WaitForSingleObject(hDemaphore,INFINITE);//
	ReleaseSemaphore(hDemaphore,1,NULL);
	Sleep(5000);	
	cout<<"主线程正在运行"<<endl;	
}