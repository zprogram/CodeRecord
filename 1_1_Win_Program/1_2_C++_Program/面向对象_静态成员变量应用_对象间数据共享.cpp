// 代码重点：静态成员变量作用
// 类的静态成员变量应用（对象间数据共享）
// 在非类的编程中，可以声明全局变量实现数据的共享。
// 然而在类中，全局变量的使用具有局限性，此时可以定义静态数据成员实现多个对象间的数据共享。



#include <iostream>
using namespace std;

class Apple
{
private:
	static int s_apples;             // 静态成员变量，表示苹果个数
	int apple;                       // 非静态变量
public:
	Apple(){    apple=5; }           // 构造函数
	void setApples(int a,int b)      // 设置苹果个数
	{
		s_apples = a;                // 静态
		apple = b;                   // 非静态
	}
	static int get_s_Apples()        // 获取静态苹果个数
	{
		return s_apples;             // 返回苹果数目
	}
	int getApple()                   // 获取非静态变量值
	{
		return apple;
	}
};
int Apple::s_apples=10;              /*初始化静态变量*/

void main()
{
	cout<<"未定义Apple类对象前，其静态成员apples="<<Apple::get_s_Apples()<<endl;
	Apple a,b;                                                //两个对象
	cout<<"未赋值前，两个对象的各自变量值如下："<<endl;
	cout<<"a.apples="<<a.get_s_Apples();
	cout<<"\na.apple="<<a.getApple()<<endl;
	cout<<"b.apples="<<b.get_s_Apples();
	cout<<"\nb.apple="<<b.getApple()<<endl;
	a.setApples(23,50);                                       //对象a赋值
	cout<<"赋值后，两个对象的各自变量值如下："<<endl;
	cout<<"a.apples="<<a.get_s_Apples();                      // 23
	cout<<"\na.apple="<<a.getApple()<<endl;                   // 50
	cout<<"b.apples="<<b.get_s_Apples();                      // 23  对象b共享了对象a设定的静态成员变量值
	cout<<"\nb.apple="<<b.getApple()<<endl;                   // 5 
}