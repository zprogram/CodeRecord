#include <iostream>
using namespace std;

void main()
{
	cout<<"----------古典兔子问题-----------\n";
	int i;//月数
	int F[30]={1,1};//初始化前两个月兔子数
	for (i = 2; i < 30; i++)
		F[i]=F[i-2]+F[i-1];//计算后28个月兔子数
	for(i=0;i<30;i++)//输出兔子数
	{
		if(i%5==0)//每隔5个换行
			cout<<"\n";
		cout<<F[i]<<"\t";
	}
	cout<<"\n";
}