// 类+算法
// 实现判断两个人谁跑得快，判断标准为各自的平均速度，如果平均速度大，则视为跑得快。

#include <iostream>
using namespace std;

class speed
{
public:
	speed(double a,double b)
	{
		_time=a;
		_distance=b;
	}
	~speed(){}
	double cal_speed()
	{
		return _distance/_time;
	}
private:
	double _time;     //时间
	double _distance; //距离
};
void main()
{
	speed peop1(1.5,5000);                      //花1.5小时跑了5千米
	speed peop2(1,3000);                        //花了1小时跑了3千米
	if(peop1.cal_speed()>peop2.cal_speed())     //如果1大于2
		cout<<"第一个人比第二个人跑得快"<<endl;
	else if(peop1.cal_speed()<peop2.cal_speed())//如果2大于1
		cout<<"第二个人比第一个人跑得快"<<endl;
	else
		cout<<"两个人跑得一样快"<<endl;
}