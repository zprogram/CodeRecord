// 代码重点：this指针
// 每个类对象在实例化时都有一个this指针指向其数据的首地址。
// 当类的非静态成员函数在访问非静态成员变量时，若遇到形参变量和成员变量相同，可以使用this指针指向成员变量，以示区别。


#include <iostream>
using namespace std;

class A
{
private:
	int num;//成员变量
public:
	A(int num)//构造函数
	{
		num=num;            //如果形参与成员变量同名，会出现错误，显示结果 num=-858993460
		//this->num=num;    //初始化，解决成员变量指针指向问题
	}
	void output()
	{
		cout<<"私有成员变量num="<<num<<endl;
	}
};

void main()
{
	A a(10);//定义类对象
	a.output();//输出
}