#include <iostream>
#include <stdlib.h>
using namespace std;

//当用字符数组表示字符串，事先并不知道所定义的字符数组应该多大，所以其大小都必须以大为主，以免在赋值的过程中越界。
//但是如果赋值的字符串大小小于字符数组的长度，会有0内存，造成内存的浪费，此时就需要将0内存删除。


#define M 30

//删除0内存
void delZero(char *ch, int size)
{
	int length=size;                  // 循环目标内存
	for(int i=0;i<size;i++)
	{
		if(ch[i]==' ')                // 如果为0
		{
			for(int j=i;j<size;j++)   // 0后的元素移前
				ch[j]=ch[j+1];        // 内存长度减1
			length--;
			i--;
		}
	}
	ch=new char[length];
}
void main()
{
	char *ch_test;
	ch_test=new char[M];                                 // 试验数组
	strcpy(ch_test,"ak dfl jak df     ");                // 赋值
	cout<<"试验的字符数组为："<<ch_test<<"在这里"<<endl; 
	delZero(ch_test,M);                                  // 调用除0函数
	cout<<"整理内存后："<<endl;
	cout<<ch_test<<"在这里"<<endl;
	free(ch_test);                                       // 释放内存
	ch_test=NULL;
}