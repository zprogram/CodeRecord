#include <iostream>
#include <fstream>
using namespace std;

// 模拟文件流状态的判定，可以使用以下函数判定文件流状态。
// （1） is_open()
//  判断打开文件是否成功，成功则返回true，否则返回false
// （2） good()
//  操作是否成功，成功则返回true，否则返回false
// （3） fail()
//  与上相反，操作失败则返回true，否则返回false
// （4） bad()
//  操作为非法，则返回true，否则返回false
// （5） eof()
//  判断是否到达文件尾，是则返回true，否则返回false
//  本实例打开文件in.txt，并读取内容。


void main()
{
	ifstream fin;                 // 输入流对象
	char ch;                      // 字符变量
	fin.open("in.txt");           // 打开文件
	if(fin.is_open())             // 成功打开
	{
		cout<<"成功打开文件"<<endl;
		if(fin.eof())             // 到达文件尾
			cout<<"已到文件尾"<<endl;
		else                      // 没到尾
		{
			cout<<"没到文件尾"<<endl;
			fin>>ch;              // 读取一个字符
			if(fin.good())        // 读取成功
				cout<<"读取成功，字符为："<<ch<<endl;
			else//读取失败
				cout<<"读取失败"<<endl;
		}
	}
	else//打开失败
		cout<<"文件没被打开"<<endl;
}