#include <iostream>
using namespace std;

/*学校的图书管理系统一般有以下多个功能：
借书、还书、图书分类管理、图书基本信息管理、当前图书状态查询等等*/
int main()
{
	cout<<"图书管理系统功能："<<endl;
	cout<<"1-借书功能管理"<<endl;
	cout<<"2-还书功能管理"<<endl;
	cout<<"3-图书分类管理"<<endl;
	cout<<"4-图书基本信息管理"<<endl;
	cout<<"5-当前图书状态查询功能"<<endl;
	cout<<"0-退出"<<endl;
	int status;
	int count = 10;

	while(count!=0)
	{
		cout<<"请输入您当前的选择：";
		cin>>status;

		if(status == 0)//退出
		{
			cout<<"退出成功!"<<endl;
			break;
		}
		else if(status == 1)//借书
			cout<<"进入借书功能管理模块!"<<endl;
		else if(status == 2)//还书
			cout<<"进入还书功能管理模块!"<<endl;
		else if(status == 3)//图书分类管理
			cout<<"进入图书分类管理模块!"<<endl;
		else if(status == 4)//图书基本信息
			cout<<"进入图书基本信息管理模块!"<<endl;
		else//查询当前图书状态
			cout<<"进入当前图书状态查询功能!"<<endl;
		count--;
	}

	return 0;
}