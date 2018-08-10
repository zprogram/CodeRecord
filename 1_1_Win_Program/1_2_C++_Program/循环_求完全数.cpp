#include <iostream>
using namespace std;


// 求完全数
// 完全数（Perfect number），又称完美数或完备数，是一些特殊的自然数。
// 它所有的真因子（即除了自身以外的约数）的和（即因子函数），恰好等于它本身。
// 如果一个数恰好等于它的因子之和，则称该数为“完全数”。
// 第一个完全数是6，第二个完全数是28，第三个完全数是496，后面的完全数还有8128、33550336等等。


int main()
{
	int shu;//变量数字
	cout<<"请输入一个任意的自然数："<<endl;
	cin>>shu;//输入数字
	//求输入数字的所有真因子
	int *zhen_yinzi = new int[shu];//不知道真因子有多少个，所以用指针指向
	int index = 0;//个数索引变量，初始化为0
	int sum = 0;//所有真因子的总和
	zhen_yinzi[0] = 1;//所有数字都有一个真因子为1
	for (int i = 2; i < shu; i++)//循环找所有因子
	{
		if(shu % i == 0)//表示该因子为真因子
		{
			index ++;
			zhen_yinzi[index] = i;
		}
	}

	for(int j = 0; j <= index; j++)//将所有真因子加和
	{
		sum += zhen_yinzi[j];
	}
	delete[] zhen_yinzi;//释放内存
	zhen_yinzi = NULL;

	if(sum == shu)//如果真因子之和等于数字本身，即为完数
		cout<<"数字"<<shu<<"是完数"<<endl;
	else
		cout<<"数字"<<shu<<"不是完数"<<endl;

	return 0;
}