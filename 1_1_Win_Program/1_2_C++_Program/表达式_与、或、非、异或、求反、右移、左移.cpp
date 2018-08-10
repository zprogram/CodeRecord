#include <iostream>
using namespace std;

int main()
{
	int a = 10;
	int b = 2;
	int c;
	c = a & b;//按位与
	cout<<"对a和b进行按位与后的结果为："<<c<<endl;
	c = a | b;//按位或
	cout<<"对a和b进行按位或后的结果为："<<c<<endl;
	c = a ^ b;//按位异或
	cout<<"对a和b进行按位异或后的结果为："<<c<<endl;
	c = ~a;//按位求反
	cout<<"对a进行按位求反后的结果为："<<c<<endl;
	c = a<<1;//左移1位
	cout<<"对a向左移动1位后的结果为："<<c<<endl;
	c = a>>1;//右移1位
	cout<<"对a向右移动1位后的结果为："<<c<<endl;


	return 0;
} 