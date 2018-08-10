#include <windows.h>
#include <iostream>
using namespace std;

HANDLE hThread1;//线程1句柄
HANDLE hThread2;//线程2句柄

DWORD WINAPI ThreadProc1(LPVOID lpParameter)
{
	cout<<"线程hThread1正在被调用"<<endl;
	return 0;
}
DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	cout<<"线程hThread2正在被调用"<<endl;
	return 0;
}
void main()
{
	hThread1=CreateThread(NULL,0,ThreadProc1,NULL,0,NULL);//创建线程1
	hThread2=CreateThread(NULL,0,ThreadProc2,NULL,0,NULL);//创建线程2
	Sleep(1000);//睡一会儿
	CloseHandle(hThread1);//关闭线程1
	CloseHandle(hThread2);//关闭线程2
	cout<<"主线程正在运行"<<endl;
}