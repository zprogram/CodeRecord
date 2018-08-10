#include <iostream>
using namespace std;


//  模拟栈空间

//以标识判断该栈还能否读写，当为false时不能读写，元素入栈，栈顶抬高。
//
//当栈顶数据已经满了，就输出栈的数据。当为true时，不能读写；


#define M 10

int main()
{
	int aa[M];                  // 定义长度为M的数组
	bool flag = false;          // 初始时false为可以读写
	int i = 0;                  // 进栈索引变量 i
	int j = M;                  // 进栈索引变量 j
	while (flag == false)       // 如果可以读写继续循环 
	{
		if (i > M - 1)          // 进栈已经满了，开始出栈
		{
			j--;                // 出栈索引减1
			if (j == 0)         // 到栈底 
				flag=true;      // 不能再读写
			cout<<aa[j]<<" ";	// 出栈		
		}
		else
		{
			cin >> aa[i];       // 入栈
			i++;                // 栈抬高
		}
	}
	cout<<endl;
	return 0;
}