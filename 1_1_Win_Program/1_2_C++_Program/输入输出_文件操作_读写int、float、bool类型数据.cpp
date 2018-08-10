#include <iostream>
#include <fstream>
using namespace std;

// 读写记事本
// 利用流输入/输出操作符写字符串到文件。
// 读写int、float、bool类型数据


void main()
{
	ofstream fout;                        //输出流
	fout.open("out.txt");                 //打开文件，如果没有，先创建
	int data1=4,data1_copy=0;             //3个写出数据
	float data2=4.5,data2_copy=.0;
	bool flag=true,flag_copy=false;
	fout<<data1<<" "<<data2<<" "<<flag;   //写出
	fout.close();                         //关闭

	ifstream fin;                                             //输入流
	fin.open("out.txt");                                      //打开记事本
	fin>>data1_copy>>data2_copy>>flag_copy;                   //读入
	cout<<data1_copy<<'\n'<<data2_copy<<'\n'<<flag_copy<<'\n';//输出到屏幕
	fin.close();                                              //关闭
}