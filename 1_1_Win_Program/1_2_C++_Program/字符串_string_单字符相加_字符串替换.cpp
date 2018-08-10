#include <iostream>
#include <string>
using namespace std;


int main()
{
	//string字符串与单字符相加
	string strC = "I love C++";
	char ch = '?';
	string str1 = "";
	str1 = strC + ch;
	cout << str1 << endl;
	//string字符串替换
	string str="Hello World";  //被替换字符串
	string str2="C++";         //替换字符串
	str.replace(6,5,str2);     //替换，从第6位字符开始，删除之后的5个字符。 
	cout<<str<<endl;           //输出结果

	return 0;
}