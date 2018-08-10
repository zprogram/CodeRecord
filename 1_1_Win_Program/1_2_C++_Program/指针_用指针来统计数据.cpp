#include <iostream>
using namespace std;

// 用指针来统计数据
// 统计每个国家的男女人数，一共有20个人，来自不同的国家。其中男人用0表示，女性用1表示。
// 来自的国家分为A国、B国和C国，各自用0、1、2表示。
// 统计来自3个国家的男女性各多少人，一共多少人。


// ROW = 男，女
// COL = 国家


#define ROW 20
#define COL 2

void main()
{
	int people[ROW][COL]={{0,0},{1,1},{1,2},{0,2},{0,1},{0,0},
	{1,0},{1,2},{1,1},{1,0},{0,2},{0,1},{0,0},
	{0,2},{1,2},{1,1},{1,0},{1,2},{0,2},{1,1}};
	int *num=new int[6];//分别为ABC的男女
	for(int i=0;i<6;i++)
		num[i]=0;
	for(int i=0;i<ROW;i++)  //取第几行数组
	{
		switch(*(*(people+i)+1))  //取每一行的第二个值，索引值从0开始
		{
		case 0://A国
			if(*(*(people+i)+0)==0)//男  //如果不是男，那就是女
				(*num)++;
			else
				(*(num+1))++;
			break;
		case 1://B国
			if(*(*(people+i)+0)==0)//男
				(*(num+2))++;
			else
				(*(num+3))++;
			break;
		case 2://C国
			if(*(*(people+i)+0)==0)//男
				(*(num+4))++;
			else
				(*(num+5))++;
			break;
		default:
			break;
		}
	}
	cout<<"来自ABC的男女人数依次为：";
	for(int i=0;i<6;i++)
		cout<<*(num+i)<<" ";   //先输出男，再输出女
	cout<<endl;
	cout<<"来自A国的人数有："<<(*num)+(*(num+1))<<endl;  // A国 男人 加 女人
	cout<<"来自B国的人数有："<<(*(num+2))+(*(num+3))<<endl; 
	cout<<"来自C国的人数有："<<(*(num+4))+(*(num+5))<<endl;
}