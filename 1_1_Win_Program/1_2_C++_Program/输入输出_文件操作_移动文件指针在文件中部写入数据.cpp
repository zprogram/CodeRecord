#include <fstream>
#include <iostream>
using namespace std;

// 移动文件指针在文件中部写入数据


int main()
{
	ofstream out("out.txt", ios::out | ios::in); //打开文件
	if (out.is_open())
	{
		out.seekp(21, ios::beg);    // 移动文件指针
		out.write(" world", 6);     // 写入
	}
	else 
	{
		cout << "out.txt 不存在" << endl;
	}
	out.close();        // 关闭

}