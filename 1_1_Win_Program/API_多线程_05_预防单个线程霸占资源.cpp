#include <windows.h>
#include <iostream>
using namespace std;


// 预防单个线程霸占资源
// 利用临界区执行线程同步的速度非常快，一个线程在退出临界区还没等到另一个线程反应过来，
// 就已经重复抢夺资源。
// 因此造成了只有一个线程在运行，本实例在每个线程退出临界区后都睡一会儿觉，再开始抢夺资源。

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
		Sleep(1000);//睡一会儿
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
		Sleep(1000);//睡一会儿
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