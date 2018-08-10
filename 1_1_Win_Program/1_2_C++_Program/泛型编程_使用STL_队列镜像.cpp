#include <iostream>
#include <queue>
#include <list>
using namespace std;

//输出一个队列的镜像，两个队列的元素呈镜面对称。
//实现过程是将原队列的元素反转赋给镜像队列。


void main()
{
	queue<int> qu;//创建队列
	queue<int> qu_copy;//复件，用于存储镜像队列
	list<int> l;//链表
	list<int>::iterator lit;//链表迭代器

	qu.push(1);//原队列压入元素
	qu.push(2);
	qu.push(3);
	qu.push(4);

	cout<<"原队列元素：";
	while(qu.empty()!=true)//如果不为空
	{
		l.push_front(qu.front());//首元素读出
		cout<<qu.front()<<" ";//输出
		qu.pop();//首元素出队列
	}
	cout<<endl;
	for(lit=l.begin();lit!=l.end();lit++)//遍历链表元素
	{
		qu_copy.push(*lit);//压入镜像队列
	}	
	cout<<"镜像队列元素：";
	while(qu_copy.empty()!=true)//如果不为空
	{
		cout<<qu_copy.front()<<" ";//输出镜像队列元素
		qu_copy.pop();
	}
	cout<<endl;
}