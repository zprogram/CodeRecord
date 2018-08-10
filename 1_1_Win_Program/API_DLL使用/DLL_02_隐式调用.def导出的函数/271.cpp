#pragma comment(lib,"270.lib")
#include <iostream>
using namespace std;


// *关键词extern提示程序链接到其他模块中寻找函数定义

extern void _stdcall find_sushu(int range_max);

void main()
{
	int n;
	cout<<"--------判断素数----------"<<endl;
	cout<<"请输入最大素数检测界限值：";
	cin>>n;//输入素数
	find_sushu(n);//调用函数
	system("pause");
}