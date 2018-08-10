//实例112  求圆的面积和周长

// 代码重点：类成员权限

// 类中只有访问类型为public的成员才可以被外部访问

#include <iostream>
using namespace std;

#define Pi 3.14159265
class circle
{
public:
	double area(double x)
	{
		return Pi*x*x;
	}
	double circumfer(double y)
	{
		return 2*Pi*y;
	}
public:
	double radius;
};
void main()
{
	circle _circle;
	cout<<"请输入圆的半径：";
	cin>>_circle.radius;
	cout<<"圆的面积为："<<_circle.area(_circle.radius)<<endl;
	cout<<"圆的周长为："<<_circle.circumfer(_circle.radius)<<endl;
}