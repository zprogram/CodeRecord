#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <iostream>
#include <windows.h>
using namespace std;


#define MAX 100
#define MIN 0

void  gene_rand() 
{ 
	int data;//随机数据
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<10;j++)
		{
			data=MIN+(int)(MAX*rand()/(RAND_MAX+MIN));//生成随机数
		}
	}		
}
LONG64 getTime()//获取CPU当前精确时间
{
	LARGE_INTEGER litmp;
	LONG64 QPart;//时间类型变量
	QueryPerformanceCounter(&litmp);//获取当前时间
	QPart=litmp.QuadPart;//获取结构体中longlong型数据
	return QPart;
}
void main()
{
	srand((int)time(0));//利用系统时间产生随机序列的种子值
	LONG64 QPart1,QPart2;
	double d=.0;//算法时间
	QPart1=getTime();//执行算法前时间
	gene_rand();//随机数据生成算法
	QPart2=getTime();//执行算法后时间
	d=(double)(QPart2-QPart1);//算法耗时
	cout<<"生成100个随机数据（不打印）,当前耗时"<<d<<"微秒"<<endl;
}