#include <iostream>
using namespace std;

// 删除数组中的指定元素


// 刚开始指针获取地址时都会被赋值数组的第0位元素地址，通过移动指针可以达到上诉目的。
// 定义字符数组ch[]和整型指针变量ptr，并将字符数组的起始地址赋给ptr，然后删除ch中中间的那位元素。

int main()
{
	char ch[]="ajfdklsafj";

	for(int i=strlen(ch)/2;i<strlen(ch);i++)//删除第strlen(ch)/2个元素
		ch[i]=ch[i+1];
	cout<<ch<<endl;
	return 0;
}