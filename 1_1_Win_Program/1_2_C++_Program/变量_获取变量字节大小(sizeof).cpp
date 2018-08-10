#include <iostream>
using namespace std;

int main()
{
	int a = 6;//一个整型变量
	int int_size;//整型变量的字节大小
	int_size = sizeof(a);

	cout<<"变量a所占的字节大小为："<<int_size<<endl;

	return 0;
}