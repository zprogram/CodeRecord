#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <iostream>
using namespace std;
 
int  main() 
{ 
	int i,result;         //定义变量，表示循环次数
	srand((int)time(0));  //利用系统时间产生随机序列的种子值
	int count[6]={0};     //1-6的统计个数
	for(i=0;i<10000;i++)  
	{
		result=1+(int)(6.0*rand()/(RAND_MAX+1.0));//设置出现1-6之间的整数
		switch(result)
		{
		case 1:
			count[0]++;  //出现一次就将对应的值自增一次
			break;
		case 2:
			count[1]++;
			break;
		case 3:
			count[2]++;
			break;
		case 4:
			count[3]++;
			break;
		case 5:
			count[4]++;
			break;
		case 6:
			count[5]++;
			break;
		}
	}

	cout<<"1-6点的出现概率依次为：";
	for(int k =0;k<6;k++)     //打印每点出现的概率
		cout<<count[k]/10000.0<<",";

	cout<<endl;

	return 0;
} 

