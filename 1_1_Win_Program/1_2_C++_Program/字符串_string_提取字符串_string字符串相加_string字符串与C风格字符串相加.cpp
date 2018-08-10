#include <iostream>
#include <string>
using namespace std;


int main()
{

	//提取string字符串的子串
	string str = "Hello World";
	string sub_str = "";
	sub_str = str.substr(0, 5);
	cout << sub_str << endl;

	//把两个string字符串相加
	string str1 = "I love";
	string str2 = " C++";
	string str3 = "";
	str3 = str1 + str2;
	cout << str3 << endl;

	//string字符串与C风格字符串相加
	string strS="Hello";
	char *ch="World";
	char *ch1="C++";
	string strC="";
	strC=strS+ch;              //第一种方式
	cout<<strC<<endl;
	strC.append(ch1);          //第二种方式
	cout<< strC <<endl;

	return 0;
}