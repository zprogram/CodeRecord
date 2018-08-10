#include <iostream>
#include <fstream>
using namespace std;

// 获得文件长度

// 通过移动文件指针至文件末尾
// 获取其当前位置得到文件长度


void main()
{
	ifstream fin("D:\\20171111-test_bin2hex.txt");
	fin.seekg(0, ios::end);              //设置文件指针到文件流尾部
	streampos ps = fin.tellg();          //读取文件指针的当前位置
	cout<<"文件长度为："<<ps<<endl;
	fin.close();                          //关闭文件流
}