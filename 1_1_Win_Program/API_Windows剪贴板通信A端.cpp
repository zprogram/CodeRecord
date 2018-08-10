#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	cout<<"---------Windows剪贴板A端---------"<<endl;
	HWND hWnd = GetClipboardOwner();      //获取剪贴板的窗口句柄
	DWORD dwLength=10;
	HGLOBAL data;                        //全局内存
	data = GlobalAlloc(GMEM_DDESHARE,dwLength+1);//分配内存
	char *pdata;                  //先定义再初始化
	pdata=(char*)GlobalLock(data);//加锁
	for(int i=0;i<dwLength;i++)
		pdata[i]=char(i+97);   //赋值
	GlobalUnlock(data);        //解锁
	if(!OpenClipboard(hWnd))   //没打开剪贴板
	{
		cout<<"剪贴板打开失败"<<endl;
		return;
	}
	EmptyClipboard();              //清空原有剪贴板内容
	SetClipboardData(CF_TEXT,data);//发送数据到剪贴板
	CloseClipboard();              //关闭剪贴板
	cout<<"数据"<<pdata<<"成功复制数据到剪贴板"<<endl;
}