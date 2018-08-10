#include <iostream>
using namespace std;


//指针有个变量类型叫做void*，可以指向任意类型的数据，即任意类型的指针都可以赋值给void*，但反过来，void*不可以赋值给其他类型的指针，除非采用强制类型转换。

void decrease(void* data, int psize)   //函数 空指针参数
{
	switch(psize)
	{
	case 1:
		char* pchar;
		pchar=(char*)data;            //void*转换为char型
		--(*pchar);
		break;
	case sizeof(int):
		int *pint;
		pint=(int*)data;              //void*转换为int型
		--(*pint);
	}
}

int main()
{
	char a='d';
	int b=102;
	// 实现任意类型变量减1功能，只实现char型和int型变量的功能操作
	decrease(&a,sizeof(a));
	decrease(&b,sizeof(b));
	cout<<a<<","<<b<<endl;  //输出结果 c , 101

	return 0;
}