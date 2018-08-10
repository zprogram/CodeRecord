#include <iostream>
using namespace std;

// 定义类A和类B ，都有私有成员变量a，都利用成员函数getVar（）返回成员变量a的值。
// 定义模版函数计算不同类对象的成员变量之和。


class A//类A
{
private:
	int a;//成员变量
public:
	A(int x){a=x;}//构造函数
	int getVar() const{return a;}//返回私有变量值
};
class B//类B
{
private:
	int a;//成员变量
public:
	B(int x){a=x;}//构造函数
	int getVar() const{return a;}//返回私有变量值
};
template<class T1,class T2> void add(T1 t1,T2 t2)//函数模板
{
	cout<<"AB对象的和："<<t1+t2<<endl;
}
void main()
{
	A _a(5);//类A对象
	B _b(4);//类B对象
	add(_a.getVar(),_b.getVar());//AB对象和
}