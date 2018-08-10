#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// 输出域宽设置只对字符串有效，使用setw()函数完成设置。如果设置宽度大于字符串宽度，按设置宽度输出。反之按实际宽度输出。


void main()
{
	string str1="Hello World";//字符串1
	string str2("I love C++");//字符串2
	cout<<setiosflags(ios::left)<<setw(20)<<str1;//宽度20
	cout<<"在这里"<<endl;//输出标志
	cout<<setiosflags(ios::left)<<setw(10)<<str2;//宽度10
	cout<<"在这里"<<endl;//输出标志
}