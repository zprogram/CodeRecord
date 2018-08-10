#include <iostream>
using namespace std;

// 类似于函数模版，类模板也可以含有多个类型参数。
// 模拟类模板的两个成员变量分属不同的类型，并初始化后输出其值。

template <class T1,class T2>//类模板有两个类型参数
class multitype
{
private://私有变量
	T1 x;
	T2 y;
public:
	multitype(T1 t1,T2 t2);//构造函数
	void show();//显示变量值
};
template <class T1,class T2>
multitype<T1,T2>::multitype(T1 t1,T2 t2)
{
	x=t1;//赋值
	y=t2;
}
template <class T1,class T2>
void multitype<T1,T2>::show()
{
	cout<<x<<" "<<y<<"\n";
}
void main()
{
	multitype<int,double> m(1,2.1);//定义对象
	m.show();//显示
}