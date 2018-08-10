#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 1、读写二进制文件
// 先写出二进制文件，再读入，文件名为out.me 
// 输出的内容为 IloveC++
// 2、读入 out.me文件内容
// 输出到屏幕

void main()
{
	ofstream fout;                  //输出流对象
	fout.open("out.me",ios::binary);//打开
	fout<<"IloveC++"<<'\n';         //写出
	fout.close();                   //关闭

	ifstream fin;                  //输入流对象
	fin.open("out.me",ios::binary);//打开
	string str;
	fin>>str;                      //读入
	cout<<str<<endl;               //输出屏幕
	fin.close();                   //关闭
}