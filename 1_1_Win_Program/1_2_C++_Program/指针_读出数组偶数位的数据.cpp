#include <iostream>
using namespace std;
//隐藏数据
// 模拟只读写位于内存中偶数位置的数据，比如内存中存有数据HIellolvoe,,Wco+r+l d
// 但读出的数据是Hello, World
// 实现：
// 定义字符数组ch，初始化为HIellolvoe,,Wco+r+l d。在字符数组的长度内实现while循环以读出位于偶数位的数据。

void main()
{
	char ch[]="HIellolvoe,,Wco+r+l d";
	int i=0;
	while(i<strlen(ch))//没有到字符数组末尾
	{
		if(i%2==0)//读出位于偶数位的数据
			cout<<ch[i];
		else
		{	}
		i++;//读下一位
	}
}


//输出结果
//Hello, World