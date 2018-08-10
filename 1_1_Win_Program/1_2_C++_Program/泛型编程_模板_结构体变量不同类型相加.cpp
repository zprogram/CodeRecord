#include <iostream>
using namespace std;


// 定义结构体var 包含5个变量
// 2个整型、3个double型、在main()中分别初始化结构体变量_var的各个变量值，并输出2个整型及3个double型变量的加法结果。


struct var    //结构体var
{
	int var_int1;
	int var_int2;
	double var_dou1;
	double var_dou2;
	double var_dou3;
};
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
	var _var;//结构体变量
	_var.var_int1=3;
	_var.var_int2=2;
	_var.var_dou1=1.345;
	_var.var_dou2=3.145;
	_var.var_dou3=9.568;
	cout<<"结构体var中两个整型变量的加运算结果为："<<add(_var.var_int1,_var.var_int2)<<endl;//整型加法
	cout<<"结构体var中三个double型变量的加运算结果为："<<add(_var.var_dou1,_var.var_dou2,_var.var_dou3)<<endl;//浮点加法
}