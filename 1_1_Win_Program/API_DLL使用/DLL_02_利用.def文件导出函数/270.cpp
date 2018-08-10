#include <iostream>
using namespace std;

// 利用.def文件导出函数
// 使用该方式导出函数需要添加一个.def文件。
// 用于编辑被导出的函数。
// 要在编译项目中(VS2015),属性->链接器->输入->模块定义文件的选项中输入.def文件的全称。
// ; 270Def.lib: 导出DLL函数
// LIBRARY 270      // (dll名称这个并不是必须的，但必须确保跟生成的dll名称一样)
// EXPORTS
// find_sushu       @ 1

void _stdcall find_sushu(int range_max) 
{
	int *num=new int[range_max+1];//申请内存
	for(int i=0;i<=range_max;i++)//赋值
		num[i]=i;
	for(int j=2;j<=range_max;j++)//由大于2的值为一个因子
	{
		if(num[j]!=0)//没确定为合数
		{
			for(int k=2;k*j<=range_max;k++)//由大于2的值为另一个因子
				num[k*j]=0;//此值重新赋为0
		}
	}
	for(int n=2;n<=range_max;n++)//输出范围内所有素数
	{
		if(num[n]!=0)//不为0即为素数
		{
			static int count=0;//计数
			cout<<num[n]<<" ";//输出素数
			count++;
			if(count%5==0)//5个数为一行
				cout<<endl;
		}
	}
	cout<<endl;
	delete []num;
	num=NULL;
}