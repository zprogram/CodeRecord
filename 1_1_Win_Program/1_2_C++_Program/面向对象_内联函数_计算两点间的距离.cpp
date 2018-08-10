// 代码重点；内联函数
// 在类内部被声明又被定义的函数成为内联函数，它的应用是解决函数调用的效率问题。
// 一般的调用函数，在进入被调用函数的地址前，先保存现场，
// 在转入函数地址。待被调用函数执行完后，转回先前的地址，恢复现场，继续执行。
// 而内联函数的使用是将该函数体直接放到当前执行地址，因此提升了效率。


#include <iostream>
using namespace std;

class Line
{
private:
	int x1,y1,x2,y2;
public:
	Line();                                             // 默认构造函数
	Line(int a = 0, int b = 0, int c = 0, int d = 0);   // 带参数的构造函数
	void printPoint();                                  // 打印两点坐标
	double getDis();                                    // 计算两点距离
};
inline Line::Line(int a,int b,int c,int d)              // 初始化点
{
	x1=a;
	y1=b;
	x2=c;
	y2=d;
}
inline void Line::printPoint()
{
	cout<<"A:("<<x1<<","<<y1<<")"<<endl;
	cout<<"B:("<<x2<<","<<y2<<")"<<endl;
}
inline double Line::getDis()
{
	double dis;
	dis=sqrt(double(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))));
	return dis;
}
void main()
{
	Line line(10,68,-5,6);
	line.printPoint();
	cout<<"两点距离："<<line.getDis()<<endl;
}