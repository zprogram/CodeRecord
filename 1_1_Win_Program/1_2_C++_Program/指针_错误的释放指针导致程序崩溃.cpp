#include <iostream>
using namespace std;

void main()
{
	int *aa=new int[10];
	int *copy_aa=aa;
	cout<<hex;//十六进制输出
	for(int i=0;i<10;i++)
	{
		*aa=i;                           //这里对指针进行赋值，将指针移向下一个元素
		cout<<aa<<" "<<*aa<<endl;
		aa++;
	}
	cout<<endl<<"当前指针指向内存的地址为："<<aa<<endl;   //指针已经超出内存块aa的边界
	//这一行很重要，如果没有将当前指针指回内存块的首地址，运行后就会出错。
	//aa=copy_aa;                          //将开辟出来的指针地址指回内存块的首地址
	delete[] aa;
	aa=NULL;
}