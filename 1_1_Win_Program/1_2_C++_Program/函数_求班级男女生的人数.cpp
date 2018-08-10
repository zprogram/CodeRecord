#include <iostream>
using namespace std;

// 求班级男女生的人数

//第1、3个参数为输入参数，第2个为输出参数，用以表示男女性别分别为0和1的区别
void fenlei(int* a, int* b, int length)
{
	for(int i=0;i<length;i++)
	{
		if(a[i]==0) //男女人数，元素0为男，元素1为女
			b[1]++;
		else if(a[i]==1)
			b[0]++;
	}
}
void main()
{
	int sex_banji[10]={1,1,0,0,0,1,0,0,1,1};//0-female，1-male
	int num[2]={0};//男女人数，元素0为男，元素1为女
	fenlei(sex_banji,num,10);
	cout<<"男女人数分别为："<<num[0]<<","<<num[1]<<endl;
}