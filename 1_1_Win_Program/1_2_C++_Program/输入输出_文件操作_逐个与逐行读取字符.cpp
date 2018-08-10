#include <iostream>
#include <fstream>
using namespace std;

void main()
{
	ifstream fin;         //输入流
	fin.open("out.txt");  //打开
	char ch[20]={'a'};    //C风格字符串
	char ch1[20]={'a'};
	// 先逐个读取字符，第一行的字符刚好12个
	for(int i=0;i<12;i++)
	{
		fin.get(ch[i]);    //一个个读取，共读12个
		cout<<ch[i];
	}
	cout<<endl;
	// 再逐行读取字符，每行取20个字符
	fin.getline(ch1,20);   //读取第2行
	cout<<ch1<<endl;
	fin.close();//关闭
}