#include <windows.h>
#include <iostream>
using namespace std;


// 运用临界区可以实现线程同步
// 即线程访问公共资源必须一个一个的进行。
// 本示例定义两个线程，轮番输出全局变量的值

CRITICAL_SECTION cs;//临界区结构对象
int i = 1;//共享资源

DWORD WINAPI ThreadProc1(LPVOID lpParameter)//线程1
{
	while(true)
	{
		EnterCriticalSection(&cs);//进入临界区
		if(i<50)
		{
			cout<<"线程hThread1当前访问的i值："<<i<<endl;
			i*=2;//每次乘以2
		}
		else
			break;//退出
		LeaveCriticalSection(&cs);//离开临界区
	}
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)//线程1
{
	while(true)
	{
		EnterCriticalSection(&cs);//进入临界区
		if(i<50)
		{
			cout<<"线程hThread2当前访问的i值："<<i<<endl;
			i*=3;//每次乘以3
		}
		else
			break;//退出
		LeaveCriticalSection(&cs);//离开临界区
	}
	return 0;
}
void main()
{
	cout<<"------临界区应用-------"<<endl;
	InitializeCriticalSection(&cs);//初始临界区
	HANDLE hThread1;//定义线程1
	HANDLE hThread2;//定义线程2
	hThread1=CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);//创建线程1
	hThread2=CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);//创建线程2
	CloseHandle(hThread1);//关闭线程1
	CloseHandle(hThread2);//关闭线程2
	Sleep(5000);//主线程睡一会儿
	cout<<"主线程正在运行"<<endl;
	DeleteCriticalSection(&cs);//释放临界区
}