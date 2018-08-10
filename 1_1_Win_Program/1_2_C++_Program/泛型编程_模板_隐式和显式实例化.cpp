#include <iostream>
using namespace std;

template<class T> void output(T a)
{
	cout<<a<<endl;
}

void main()
{
	//隐式实例化
	cout<<"隐式实例化输出"<<endl;
	output(1);                     //整型
	output(1.2);                   //浮点型
	cout<<"显式实例化输出"<<endl;
	//显示实例化
	output<int>(34);               //整型
	output<double>(3.1415);        //浮点型
}