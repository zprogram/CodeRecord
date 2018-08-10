#include <iostream>
using namespace std;
#include <stdio.h>

//071
int main()
{
	int array_071[5][6];
	int (*point)[6]=array_071;//数组指针   将array_071首元素赋给point数组的首元素。
	int *pointp[5];           //指针数组   
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<6;j++)
			array_071[i][j]=i+j;//初始化
	}
	//数组指针访问内存
	cout<<"*(*(point+2)+4)的元素为："<<*(*(point+2)+4)<<endl;  //第3行，第4列
	cout<<"*(point[2]+4)的元素为："<<*(point[2]+4)<<endl;      //第3行，第4列
	cout<<"(*(point+2))[4]的元素为："<<(*(point+2))[4]<<endl;  //第3行，第4列
	cout<<"point[2][4]的元素为："<<point[2][4]<<endl;          //第3行，第4列  

	for(int i=0;i<5;i++)
		pointp[i]=array_071[i];                                //将array_071每一行的首地址赋给pointp的每个元素
	//指针数组赋值
	cout<<"*(*(pointp+2)+4)的元素为："<<*(*(pointp+2)+4)<<endl;   //
	cout<<"*(pointp[2]+4)的元素为："<<*(pointp[2]+4)<<endl;
	cout<<"(*(pointp+2))[4]的元素为："<<(*(pointp+2))[4]<<endl;
	cout<<"pointp[2][4]的元素为："<<pointp[2][4]<<endl;
	return 0;
}