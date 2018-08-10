#include <iostream>
//#include <stdlib.h>
using namespace std;

void main()
{
	// 字符串变整数

	int a=0;//整型变量
	char *ch="1234";//字符串
	a=atoi(ch);//字符串转换为整型
	cout<<"字符串ch变为整数为:"<<a<<endl;//输出整数


	// 整数变字符串

	int a = 1234;//整数
	char ch[10];//字符数组
	itoa(a, ch, 10);//转换整数为字符串
	cout << "整数a变换为字符串ch，表示为：" << ch << endl;
}