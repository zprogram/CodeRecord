//实例116  错误的模糊引用（类继承问题）
// 因为Chinese和woman都从human继承了成员变量，因此此二义性错误可以通过虚继承避免


#include <iostream>
using namespace std;

class human//人类
{
public:
	bool getBeauty()
	{
		return m_beauty;
	}
	bool m_beauty;
};
class Chinese:virtual public human//中国人
{
};
class woman:virtual public human//女人
{
};
class me:public Chinese, public woman
{
public:
	me(bool a)
	{
		m_beauty=a;
	}
};
void main()
{
	me _me(true);
	cout<<_me.getBeauty()<<endl;
}