#include <sys/timeb.h>
#include <time.h>
#include <windows.h>
#include <iostream>
using namespace std;

// 实现屏幕显示时钟功能
// 每隔0.5秒更新屏幕时间，用到回调函数、定时器及系统时间获取函数。


class TIME
{
private:
	double timeM;//总时间，换算为毫秒
	int time_H;//时
	int time_M;//分
	int time_S;//秒
	double millisecond;//毫秒
public:
	void cal();//计算当前时间
	double getSystime();//获取总时间
	int getH();//获取时
	int getM();//获取分
	int getS();//获取秒
};
void TIME::cal()
{
	struct _timeb timebuffer;//时间缓冲变量
	char *timeline;
	unsigned short millitml;
	char temp_H[2];//字符变换量
	char temp_M[2];
	char temp_S[2];
	_ftime(&timebuffer);//获取缓冲量
	timeline = ctime(&(timebuffer.time));//转换为char*型
	millitml = timebuffer.millitm;//获取毫秒值
	millisecond = (double)millitml/1000;//变换为真正的毫秒

	for(int i = 0; i < 2; i++)
	{
		temp_H[i] = timeline[i+11];//从第11个字节开始为时的字符值，下同
	}
	for(int j = 0; j < 2; j++)
	{
		temp_M[j] = timeline[j+14];//分的字符值
	}
	for(int k = 0; k < 2; k++)
	{
		temp_S[k] = timeline[k+17];//秒的字符值
	}
	time_H = atoi(temp_H);//时变换为整型
	time_M = atoi(temp_M);//分变换为整型
	time_S = atoi(temp_S);//秒变换为整型
	timeM = double(time_H) * 3600 + double(time_M) * 60 + double(time_S) + millisecond;//计算总时间
}
double TIME::getSystime()
{
	return timeM;//返回总时间
}
int TIME::getH()
{
	return time_H;//返回时
}
int TIME::getM()
{
	return time_M;//返回分
}
int TIME::getS()
{
	return time_S;//返回秒
}
VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT idEvent,DWORD dwTime)//回调函数
{
	TIME t;//时间对象
	t.cal();//计算当时时间
	cout<<t.getH()<<"："<<t.getM()<<"："<<t.getS()<<endl;//输出
}
void main()
{
	int ID=1;//定时器ID
	int elapse=500;//每隔多长时间响应，单位为毫秒
	MSG msg;//消息

	SetTimer(NULL,ID,elapse,TimerProc);//定时器函数
	cout<<"当前系统时间:"<<endl;
	while(GetMessage(&msg,NULL,NULL,NULL)!=0 &&
		GetMessage(&msg,NULL,NULL,NULL)!=-1)//获取的消息不是退出也不是错误
	{
		if(msg.message==WM_TIMER)//如果收到的信息为定时器
		{
			TranslateMessage(&msg);//寄送消息到消息队列
			DispatchMessage(&msg);//发送消息到窗口程序
		}
	}
	
}