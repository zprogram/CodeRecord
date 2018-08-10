#include <windows.h>
#include <iostream>
using namespace std;

void main()
{
	cout<<"---------Windows剪贴板B端---------"<<endl;
	HWND hWnd = GetClipboardOwner();           //获取剪贴板的窗口句柄
	OpenClipboard(hWnd);                       //打开剪贴板
	if(IsClipboardFormatAvailable(CF_TEXT))    //数据格式是否为CF_TEXT
	{
		HANDLE data = GetClipboardData(CF_TEXT);//获取剪贴板数据句柄
		char *pdata;
		pdata=(char*)GlobalLock(data);            //锁定内存
		cout<<"从剪贴板获取的数据："<<pdata<<endl;//输出剪贴板中的内容
		GlobalUnlock(data);                       //内存解锁
	}
	CloseClipboard(); //关闭剪贴板
}