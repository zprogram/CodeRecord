//实例110  产量统计（计算A村各类农作物的产量）

#include <iostream>
using namespace std;


//利用类的应用实现统计A村各类农作物的产量。
//
//已知A村现有3类农作物：蔬菜、水果和稻谷。
//
//输入3类农作物的占地亩数，以及每类农作物每亩地可产出的数量，最后输出各类农作物的产量。
//
// 代码重点：类的构造函数、成员函数、变量引用

class Cun_A
{
public:
	Cun_A(double x, double y, double z)                // 带参数的构造函数
	{
		acer_veget = x;
		acer_fruit = y;
		acer_grain = z;
	}
	~Cun_A() {}                                        // 析构函数
	void SetPerProduct(double a, double b, double c)   
	{
		output_per_acerV = a;
		output_per_acerF = b;
		output_per_acerG = c;
	}
	void veget()                                       // 蔬菜
	{
		double result = acer_veget*output_per_acerV;
		cout << "A村蔬菜的产量为：" << result << endl;
	}
	void fruit()                                       // 水果
	{
		double result = acer_fruit*output_per_acerF;
		cout << "A村水果的产量为：" << result << endl;
	}
	void grain()                                       // 稻谷
	{
		double result=acer_grain*output_per_acerG;
		cout<<"A村稻谷的产量为："<<result<<endl;
	}
private:
	double acer_veget;//蔬菜作物的占地
	double output_per_acerV;//每亩地产蔬菜多少
	double acer_fruit;//水果作物的占地
	double output_per_acerF;//每亩地产水果多少
	double acer_grain;//稻谷作物的占地
	double output_per_acerG;//每亩地产稻谷多少
};
void main()
{
	Cun_A A(1.2,2,3);                 // 类对象声明    、构造函数传参
	A.SetPerProduct(500,400,700);     // 设置产量      、成员函数传参
	A.veget();                        // 计算蔬菜产量  、成员变量调用
	A.fruit();                        // 计算水果产量
	A.grain();                        // 计算稻谷产量
}
