#include <iostream>
using namespace std;

// 将内存的数据倒转过来(指针内存复制+算法)
// 实现将内存中的数据倒转并显示结果。
// 只能倒转整数数据内存。

void inv(int *a,int length)
{
	int temp;
	int i,j;
	for(i=0;i<=(length-1)/2;i++)   // 只需要从中间开始逆转
	{
		j=length-1-i;
		temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
}
int main()
{
	int memo[10]={3,4,5,6,7,8,9,9};
	cout<<"原内存数据：";
	for(int i=0;i<10;i++)
		cout<<memo[i];
	cout<<endl;
	inv(memo,10);//反转
	cout<<"反转后的内存数据：";
	for(int i=0;i<10;i++)
		cout<<memo[i];
	cout<<endl;
	return 0;
}