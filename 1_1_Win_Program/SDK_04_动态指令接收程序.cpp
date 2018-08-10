#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WinHouProc(
  HWND hwnd,      // 窗口句柄
  UINT uMsg,      // 消息标识符
  WPARAM wParam,  // 第一个消息参数
  LPARAM lParam   // 第二个消息参数
);
int WINAPI WinMain(
  HINSTANCE hInstance,      // 指向当前实例的句柄
  HINSTANCE hPrevInstance,  // 指向先前实例的句柄
  LPSTR lpCmdLine,          // 命令行
  int nCmdShow              // 显示状态
)
{
	WNDCLASS wndclass; //创建一个窗口类
	wndclass.cbClsExtra=0; //窗口类无扩展
	wndclass.cbWndExtra=0; //窗口实例无扩展
	wndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);  //窗口背景为白色
	wndclass.hCursor=LoadCursor(NULL,IDC_HAND); //窗口采用手型
	wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION); //窗口的最小化图标为缺省图标
	wndclass.hInstance=hInstance;  //当前实例句柄
	wndclass.lpfnWndProc=WinHouProc; //定义窗口处理函数
	wndclass.lpszClassName="Win32"; //窗口类名
	wndclass.lpszMenuName=NULL; //窗口无菜单
	wndclass.style=CS_HREDRAW | CS_PARENTDC; //设置窗口类型
	RegisterClass(&wndclass); //注册窗口类

	HWND hwnd;
	hwnd=CreateWindow("Win32","Win32窗口",WS_OVERLAPPEDWINDOW,
		100,50,600,400,NULL,NULL,hInstance,NULL);  //创建窗口

	ShowWindow(hwnd,SW_SHOWNORMAL);   //显示窗口
	UpdateWindow(hwnd);  //更新窗口

	MSG msg;
	while(GetMessage(&msg,NULL,0,0))//获取消息
	{
		TranslateMessage(&msg);//发送消息到消息队列
		DispatchMessage(&msg);//发送消息到窗口程序
	}
	return 0;
}
LRESULT CALLBACK WinHouProc(
  HWND hwnd,      // 窗口句柄
  UINT uMsg,      // 消息标识符
  WPARAM wParam,  // 第一个消息参数
  LPARAM lParam   // 第二个消息参数
)
{
	switch(uMsg)
	{
	case WM_CHAR:   //按键指令
		MessageBox(hwnd,"按键指令","Win32",0);
		break;
	case WM_PAINT:  //绘图
		HDC hDC;
		PAINTSTRUCT ps; 
		hDC=BeginPaint(hwnd,&ps); //获取给图所用句柄
		TextOut(hDC,20,10,"Win32窗口程序",strlen("Win32窗口程序"));  //在屏幕上输出文本
		EndPaint(hwnd,&ps);
		break;
	case WM_CLOSE:  //关闭窗口
		MessageBox(hwnd,"关闭窗口指令","Win32",0);
		DestroyWindow(hwnd); //销毁窗口
		break;
	default:
		return DefWindowProc(hwnd,uMsg,wParam,lParam); //返回窗口过程
	}
	return 0;
}