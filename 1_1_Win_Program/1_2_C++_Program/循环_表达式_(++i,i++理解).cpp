#include <iostream>
using namespace std;

//信号灯的状态时亮时灭，现计数，如果次数为偶则亮，如果次数为奇则不亮
//需要注意++的位置
int main()
{
	int count=1;
	cout<<"灭"<<endl;
	for(;count<10;)
	{
		int a;
		a = count++;
		a = ++count;
		// 汇编层面理解
		//13: 		a = count++;
		//  mov         eax, dword ptr[count]
		//	mov         dword ptr[ebp - 14h], eax; count的值先给了变量a
		//	mov         ecx, dword ptr[count]
		//	add         ecx, 1; 自增加，count的值 + 1
		//	mov         dword ptr[count], ecx
		//14: 		a = ++count;
		//  mov         eax, dword ptr[count]
		//	add         eax, 1; 自增加，count的值 + 1
		//	mov         dword ptr[count], eax
		//	mov         ecx, dword ptr[count]
		//	mov         dword ptr[ebp - 14h], ecx; 然后count的值先给了变量a

		if(a % 2 == 0)//偶数
			cout<<"亮"<<endl;
		else
			cout<<"灭"<<endl;
	}
	return 0;
}
