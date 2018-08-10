#include <iostream>
using namespace std;

//使用template可以定义函数模版，也可以定义类模版。它可以定义不同类型的对象，其定义的最简单格式如下：
//template <class T> class output//模板类
//{
	// 类模版内容
//};
//
// 以下代码实现定义类模版output，用于处理不同类型的数据，并输出

template <class T> class output//模板类
{
private:
	T _var;//变量
public:
	output(const T& v):_var(v)//构造函数
	{}
	T var()//获取成员变量值，并返回
	{return _var;}
};
void main()
{
	output<double> x(1.0);    //double型对象
	output<int> j(3);         //int型对象
	output<char*> str("5.0"); //字符串对象
	cout<<x.var()<<endl;
	cout<<j.var()<<endl;
	cout<<str.var()<<endl;
}