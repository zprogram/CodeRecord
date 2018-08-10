#include <iostream>
#include <fstream>
using namespace std;

//使用流类输出一个文本文件，out.txt
//输出内容为 Hello World

void main()
{
	ofstream fout;
	fout.open("out.txt");         //打开文件
	if(fout.fail())               //如果打开失败
		cout<<"out.txt文件打开失败"<<endl;
	else
		fout<<"Hello World"<<'\n';//输出

}