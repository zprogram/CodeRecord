//代码重点：类的多态实现

// 员工月薪发放

// 演示员工月薪的发放，现有基类salary，子类member1、member2都继承自类salary。
// 实现当利用基类给员工member1、member2发月薪时，按照各自的情况执行。



#include <iostream>
using namespace std;

class salary
{
public:
	salary(){}
	~salary(){}
	virtual void pay(){}
private:
};
class member1:public salary
{
public:
	member1(double a){_total=a;}
	~member1(){}
	void pay()
	{
		cout<<"每月给员工1的薪水为："<<_total<<"元"<<endl;
	}
private:
	double _total;
};
class member2:public salary
{
public:
	member2(double a){_total=a;}
	~member2(){}
	void pay()
	{
		cout<<"每月给员工2的薪水为："<<_total<<"元"<<endl;
	}
private:
	double _total;
};
void main()
{
	member1 m1(4000.0);
	member2 m2(10000.0);
	salary *sa1=&m1;
	salary *sa2=&m2;
	sa1->pay();
	sa2->pay();
}