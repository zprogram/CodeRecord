#include <iostream>
#include <string>
using namespace std;


// void* 也是泛型编程的一种，它可以接受任意类型的指针。
// 以下代码实现利用void*输出内存区域的各类型数据。
// 类型参数作为函数形参传入函数，根据不同的选择强制转换类型，

void output(void* p,char ch)
{
	switch(ch)
	{
	case 'a':
		{
			int *ap=(int*)p;//强制转换
			cout<<*ap<<" ";
		}
		break;
	case 'b':
		{
			char *chp=(char*)p;//强制转换
			cout<<*chp<<" ";
		}
		break;
	case 'c':
		{
			double *dp=(double*)p;//强制转换
			cout<<*dp<<" ";
		}
		break;
	case 'd':
		{
			string *strp=(string*)p;//强制转换
			cout<<*strp<<" ";
		}
		break;
	}
}
void main()
{
	int a=4;           //int
	char ch='a';       //ch
	double d=0.2145;   //double
	string str="Hello";//string
	output(&a,'a');   //输出整型
	output(&ch,'b');  //char型
	output(&d,'c');   //double型
	output(&str,'d'); //字符串
	cout<<endl;
}