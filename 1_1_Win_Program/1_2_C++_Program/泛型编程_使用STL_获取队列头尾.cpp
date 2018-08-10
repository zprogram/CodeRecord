#include <iostream>
#include <queue>
using namespace std;

//获取队列头尾

void main()
{
	queue<int> qu;//创建队列
	qu.push(1);
	qu.push(2);
	qu.push(3);
	qu.push(4);
	
	cout<<"队列头元素："<<qu.front()<<endl;//队列头
	cout<<"队列尾元素："<<qu.back()<<endl;//队列尾
}