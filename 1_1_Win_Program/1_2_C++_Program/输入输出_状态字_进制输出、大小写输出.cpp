#include <iostream>
#include <iomanip>
using namespace std;

//使用cin/cout设置其状态字，比如进制输出、大小写输出等。

void main()
{
	int a=123;//整数123
	cout<<"默认为十进制输出："<<a<<endl;
	cout<<hex<<"十六进制小写输出："<<a<<endl;
	cout<<setiosflags(ios::uppercase)<<hex<<"十六进制大写输出："<<a<<endl;
	cout<<oct<<"八进制输出："<<a<<endl;
}