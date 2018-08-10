#include <iostream>
using namespace std;

// 防止野指针
// 1.指针创建后没有初始化
// 解决方法：初始化为NULL或者指向合法的内存
// 2.指针在使用free()和delete()函数释放指向的内存时，没有释放指针
// 当程序再一次调用该指针，该野指针会乱指地址。但有些内存是受保护并且不可读写的，严重时会导致程序崩溃。
// 解决方法：在释放内存后，也将指针设为NULL
// 3.指针的创建和操作不在同一个作用域中

void main()
{
	int *a;
	int *b=new int[2];     // new方式申请内存
	int aa=10;
	a=&aa;                 // 取地址
	*b=2;
	cout<<a<<" "<<*a<<endl;
	cout<<b<<" "<<*b<<endl;
	delete[] b;            // 释放内存
 	if(b!=NULL)            // 释放指针
 		b=NULL;
}