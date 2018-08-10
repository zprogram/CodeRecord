// 代码重点：模板函数返回类型调用
// 实现万能加法计算器，函数模板可以适用于不同类型的数据进行加法运算，再也不用重载函数。
// 模拟整型及浮点型变量的加法运算


#include <iostream>
using namespace std;

template<class T> T add(T a, T b)    //模板加法函数
{
	return a+b;
}
void main()
{
	cout << add(1, 2) << endl;       //整型加法
	cout << add(1.2, 3.4) << endl;   //浮点加法
}