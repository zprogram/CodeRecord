#include <iostream>
using namespace std;

// 按位数排列(一个数位数越多越往后排）
//1
//1
//0
//21
//433
//3231
//142234

int weishu(int chushu, int shu)     
{
	double result;
	result=double(shu/chushu);    // 除数的值剩余位数结果
	int new_chushu=chushu;        // 当前的位数存储起来
	if((result>=0)&&(result<=9))  // 如果当前的位数小于1，就返回当前位数
		return new_chushu;
	else
	{
		new_chushu=chushu*10;    // 如果还没有到达最小位数就乘以10
		weishu(new_chushu,shu);  // 将数值递归到下一次函数中
	}
}

int main()
{
	int array_042[10]={1,21,3231,423,1,11,14334,15466};
	int beishu[10]={1};
	for(int i=0;i<10;i++)                          // 取出原数组对应的数值                             
		beishu[i]=weishu(1,array_042[i]);          // 对应索引值的位数
	for(int i=0;i<10;i++)
	{
		for(int j=i+1;j<10;j++)
		{
			
			if(beishu[i]<=beishu[j])               //不改变位置
			{}
			else
			{
				int temp;
				temp=array_042[i];
				array_042[i]=array_042[j];
				array_042[j]=temp;
				temp=beishu[i];
				beishu[i]=beishu[j];
				beishu[j]=temp;
			}
		}
	}
	cout<<"按位数排列后的array_042为："<<endl;
	for(int i=0;i<10;i++)
		cout<<array_042[i]<<endl;
	return 0;
}