//实例111  乡村生产总值（同类对象数据统计（ABC对象相加））

// 代码重点：运算符重载、友元函数

// 统计3个农村中的3类农作物的生产总值，即定义A、B、C三个对象，之后相加得到结果。
// 为了使类对象相加，需要重载运算符(+)。因为需要访问私有成员变量，所以定义该重载函数为友元函数。

#include <iostream>
using namespace std;

class Cun_product
{
public:
	Cun_product(){veget_result=0;fruit_result=0;grain_result=0;}  //构造函数
	Cun_product(double x,double y,double z)                       //有参数构造函数
	{
		veget_result=x;
		fruit_result=y;
		grain_result=z;
	}
	~Cun_product(){}
	friend Cun_product operator+(Cun_product cun1,Cun_product cun2);//重载友元运算符函数
	void output()                                                   //输出函数        
	{
		cout<<veget_result<<","<<fruit_result<<","<<grain_result<<endl;
	}
private:
	double veget_result;                                            //私有成员变量
	double fruit_result;
	double grain_result;
};
Cun_product operator+(Cun_product cun1,Cun_product cun2)            //运算符函数定义
{
	Cun_product add;
	add.veget_result=cun1.veget_result+cun2.veget_result;
	add.fruit_result=cun1.fruit_result+cun2.fruit_result;
	add.grain_result=cun1.grain_result+cun2.grain_result;		
	return add;
}
void main()
{
	Cun_product cun_A(1.2,3,4),cun_B(2.3,5,1),cun_C(1.4,3,2),cun;
	cun=cun_A+cun_B+cun_C;                                        //类的加法运算
	cout<<"ABC村总共的蔬菜、水果和稻谷产量分别为：";
	cun.output();
}
