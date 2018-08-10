#include <iostream>

// 模版函数的重载例子


using namespace std;

template<class T> T add(T a, T b)//模板加法函数
{
	return a+b;
}
template<class T> T add(T a, T b, T c)//重载模板加法函数
{
	return a+b+c;
}
void main()
{
	cout<<add(1,2)<<endl;//整型加法
	cout<<add(1.2,3.4,4.5)<<endl;//浮点加法
}