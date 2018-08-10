#include <iostream>
using namespace std;
// 实现一个数据查询系统，现已知数据库中包含的数据，用户根据自己的意愿查询该数据是否存在。
// 模拟火车票当日的售卖情况


struct ticket
{
	char train_number[5];//车次
	char train_name[50];//从哪儿到哪儿
	int  yingwo_num;//硬卧票数
	float yingwo_cash;//硬卧钱
	int yingzuo_num;//硬座票数
	float yingzuo_cash;//硬座钱
};
ticket Ticket[5];//数据库目前只存5条项目
// 车票信息初始化
void init()       
{
	strcpy(Ticket[0].train_number, "T56");
	strcpy(Ticket[0].train_name,"西安-北京西");
	Ticket[0].yingwo_num=100;
	Ticket[0].yingwo_cash=263.5;
	Ticket[0].yingzuo_num=200;
	Ticket[0].yingzuo_cash=148.5;

	strcpy(Ticket[1].train_number, "K126");
	strcpy(Ticket[1].train_name,"西安-天津");
	Ticket[1].yingwo_num=60;
	Ticket[1].yingwo_cash=289.5;
	Ticket[1].yingzuo_num=100;
	Ticket[1].yingzuo_cash=163.5;

	strcpy(Ticket[2].train_number, "T166");
	strcpy(Ticket[2].train_name,"西安-上海");
	Ticket[2].yingwo_num=150;
	Ticket[2].yingwo_cash=321.5;
	Ticket[2].yingzuo_num=240;
	Ticket[2].yingzuo_cash=180.5;

	strcpy(Ticket[3].train_number, "T266");
	strcpy(Ticket[3].train_name,"西安-广州");
	Ticket[3].yingwo_num=50;
	Ticket[3].yingwo_cash=414;
	Ticket[3].yingzuo_num=40;
	Ticket[3].yingzuo_cash=236;

	strcpy(Ticket[4].train_number, "T114");
	strcpy(Ticket[4].train_name,"西安-南京");
	Ticket[4].yingwo_num=10;
	Ticket[4].yingwo_cash=270.5;
	Ticket[4].yingzuo_num=20;
	Ticket[4].yingzuo_cash=152.5;
}
void query()
{
	char checi[5];
	bool flag=true;
	bool whether=false;//是否有
	while(flag==true)
	{
		cout<<"请输入要查询的车次：";
		cin>>checi;
		for(int i=0;i<5;i++)
		{
			if(strcmp(Ticket[i].train_number,checi)==0)
			{
				whether=true;
				cout<<Ticket[i].train_number<<" "<<Ticket[i].train_name;
				cout<<" "<<Ticket[i].yingwo_num<<" "<<Ticket[i].yingwo_cash;
				cout<<" "<<Ticket[i].yingzuo_num<<" "<<Ticket[i].yingzuo_cash<<endl;
				i=5;
			}
			else
				whether=false;
		}
		if(whether==true)//有
		{}
		else
		{cout<<"该车次在系统中没有相应信息，请检查后输入"<<endl;}

		cout<<"是否继续查询？0-否，1-是";
		int x;
		cin>>x;
		if(x==0)
		{
			flag=false;
			cout<<"退出查询系统"<<endl;
		}
		else if(x==1)
		{}
	}
}
int main()
{
	cout<<"------------------------火车票当日售卖查询系统---------------------"<<endl;
	cout<<"现存火车票信息只有从西安发的列车，";
	cout<<"目的地只有北京西、上海、天津、广州和南京。"<<endl;
	cout<<"请前往上述5个目的地的旅客进行查询"<<endl;
	cout<<"车次-------始地-目的地-------硬卧剩票";
	cout<<"------硬卧价钱------硬座剩票------硬座价钱"<<endl;
	init();//初始化信息
	query();//查询
	return 0;
}