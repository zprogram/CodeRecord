#include <iostream>
using namespace std;
#include <windows.h>


// 270.dll源码来自 DLL_02_利用.def文件导出函数
// typedef 目标函数返回类型 (*指针函数类型)(目标函数参数表)

// 利用显式方法调用.def导出的函数，即只用导出函数的.dll文件。
// 导出DLL要注意调用约定，否则会产生报错。
// 加入WINAPI是因为270.cpp(即DLL_02_利用.def文件导出函数)，指定了_stdcall
//
//  #define CALLBACK    __stdcall
//
//  #define WINAPI      __stdcall
//  
//  #define WINAPIV     __cdecl 



void main()
{
	typedef void(WINAPI*fff)(int);//定义指针函数
	fff find_sushu;//定义函数指针
	HINSTANCE hInst;//实例
	hInst=LoadLibrary(L"270.dll");//显式加载
	if(hInst==NULL)
	{
		cout<<"调用DLL失败"<<endl;
		return;
	}
	find_sushu=(fff)GetProcAddress(hInst,"find_sushu");//获取函数地址
	if(!find_sushu)//地址为空
	{
		cout<<"获取函数地址失败"<<endl;
		return;
	}
	int n;
	cout<<"--------判断素数----------"<<endl;
	cout<<"请输入最大素数检测界限值：";
	cin>>n;//输入素数
	find_sushu(n);//调用函数
	FreeLibrary(hInst);

	system("pause");
}