#include <windows.h>
#include <iostream>
using namespace std;

// 定时器功能

// 使用SetTimer()函数
// 实现功能是在一定时间内发送消息，输出字符串Hello World


VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent,DWORD dwTime)//回调函数
{
	cout<<"Hello World"<<endl;
}
void main()
{
	int ID=1;//定时器ID
	int elapse=1000;//每隔多长时间响应，单位为毫秒
	MSG msg;//消息

	SetTimer(NULL,ID,elapse,TimerProc);//定时器函数


	while(GetMessage(&msg,NULL,NULL,NULL)!=0 &&
		GetMessage(&msg,NULL,NULL,NULL)!=-1)//获取的消息不是退出也不是错误
	{
		if(msg.message==WM_TIMER)//如果收到的信息为定时器
		{
			cout<<"收到消息"<<endl;//打印结果
			TranslateMessage(&msg);//寄送消息到消息队列
			DispatchMessage(&msg);//发送消息到窗口程序
		}
	}

}