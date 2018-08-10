//实例113  动物对象进化（继承）

//代码重点：继承使用

// 定义了三个类，动物原型、猿、人类。

// 猿类继承动物

// 人类继承猿类

// 动物原型可以呼吸、猿类可以行走、人继承前面两个类可以呼吸、行走、也可以想念某人。


#include <iostream>
using namespace std;

class animal_ancestor                   // 动物原型
{
public:
	animal_ancestor() {}
	~animal_ancestor() {}
	void respire()                     // 呼吸
	{
		cout<<"可以呼吸"<<endl;
	}
};
class ape:public animal_ancestor       // 猿继承动物原型类
{
public:
	ape(){}
	~ape(){}
	void move()//行走
	{
		cout<<"可以行走"<<endl;
	}
};
class human:public ape                 // 人类继承猿类
{
public:
	human(){}
	~human(){}
	void miss()
	{
		cout<<"可以想念某人"<<endl;
	}
};
void main()
{
	human _human;
	cout<<"人类";
	_human.respire();
	_human.move();
	_human.miss();
}