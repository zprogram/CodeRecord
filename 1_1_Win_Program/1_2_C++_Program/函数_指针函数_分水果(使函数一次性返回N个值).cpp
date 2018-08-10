#include <iostream>
using namespace std;

// 指针函数

// 使用函数一次性返回N个值

// 一般情况下，定义的函数不返回值或者返回一个值，本示例实现使函数一次性返回N个值。

// 演示分水果过程，多种水果分别分配给对应的人数，并输出平均分配后还剩多少个。

// 返回值为数组的首地址，第1、2个参数为两个数组变量的首地址，第3个参数为数组的长度。
int* fenpei(int* a, int* b, int num)
{
	int *remain=new int[num];
	for(int i=0;i<num;i++)
		remain[i]=a[i]%b[i];             // 每种水果平均分配给每个人后还剩多少个。
	return remain;
}
void main()
{
	int fruit[5];                        //10种水果各自个数
	int num_people[5];                   //每种水果对应分配人数
	int *premain=NULL;                    
	for(int i=0;i<5;i++)                 //初始化数组
	{
		fruit[i]=100*i+1;
		num_people[i]=i+1;
	}
	premain=fenpei(fruit,num_people,5);  //调用分配函数

	cout<<"分配水果后各自还剩个数："<<endl;
	
	for(int i=0;i<5;i++)
		cout<<premain[i]<<endl;
	delete[] premain;
	premain=NULL;
}