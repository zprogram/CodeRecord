#include <iostream>
#include <string>
using namespace std;

//string与C风格字符串转换
int main()
{
	string str="Hello";
	const char *ch;
	ch=str.c_str();//string转为C风格字符串
	cout<<ch<<endl;

	ch="World";
	str=ch;//C风格字符串转为string
	cout<<str<<endl;
	return 0;
}