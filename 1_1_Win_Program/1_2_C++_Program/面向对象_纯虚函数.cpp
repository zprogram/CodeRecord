// 代码重点：纯虚函数
// 如何使用纯虚函数实现家族性格遗传。
// 下一代的性格是从上一代继承而来的，现定义积累xingge作为一个抽象类，子类child1、child2分别继承自抽象类xingge。

#include <iostream>
using namespace std;

class xingge//抽象类
{
public:
	xingge(){}//构造函数
	virtual void talk()=0;//纯虚函数
	virtual void kind_hearted()=0;//纯虚函数
};
class child1:public xingge//子类child1
{
public:
	child1(){}
	void talk()
	{cout<<"沉默寡言"<<endl;}
	void kind_hearted()
	{cout<<"热心肠"<<endl;}
};
class child2:public xingge//子类2
{
public:
	child2(){}
	void talk()
	{cout<<"碎碎念"<<endl;}
	void kind_hearted()
	{cout<<"热心肠"<<endl;}
};
void main()
{
	xingge *_xg;//抽象类指针
	child1 _c1;//child1实例化
	child2 _c2;//child2实例化
	_xg=&_c1;//取址child1
	cout<<"child1的性格："<<endl;
	_xg->talk();
	_xg->kind_hearted();
	_xg=&_c2;//取址child2
	cout<<"child2的性格："<<endl;
	_xg->talk();
	_xg->kind_hearted();
}