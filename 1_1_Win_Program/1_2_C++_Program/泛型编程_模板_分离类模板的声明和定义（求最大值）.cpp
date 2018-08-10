#include <iostream>
using namespace std;

//演示如何将一个类模板的声明和定义分离，成员函数在体外的定义格式为：

// 类
//template <class T>
//class 类名				                //类模板
//{
//};
// 成员函数

//返回值类型 类名<T>::成员函数名(参数列表)    //定义类成员函数体
//{
//	类模板内容
//}

template <class T>
class MAX				                //类模板
{
private:
	T x,y;								//变量
public:
	MAX(T v1,T v2);				        //构造函数
	T getmax(MAX &a);                   //获取最大值
};
template <class T>
MAX<T>::MAX(T v1,T v2)      //定义构造函数体
{
	x=v1;
	y=v2;
}
template <class T>
T MAX<T>::getmax(MAX &a)    //定义类成员函数体
{
	return a.x<a.y?a.y:a.x;
}
void main()
{
	MAX<int> x(1,2);//对象
	cout<<"最大值："<<x.getmax(x)<<"\n";
}