// 代码重点：模板函数参数调用
// 不理会形参的类型。
// 不同的数据类型都可以调用该函数，本示例通过函数模板输出不同类型的变量值

#include <iostream>
using namespace std;

template<class T> void output(T a)//模板输出函数
{
	cout<<a<<endl;
}
void main()
{
	output(1);   // 输出整数变量
	output(3.4); // 输出浮点变量
}