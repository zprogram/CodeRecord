#include <iostream>
using namespace std;

struct book
{
	char ch_num[3];//两个字节，最多为99
	char ch_name[100];//100个字节，最多为50个汉字
	char ch_author[10];//10个字节，最多为5个汉字
	char ch_publisher[50];//50个字节，最多为25个汉字
};
int main()
{
	book Book[100];//数据库只能存100条项目
	int number=5;//初始化为5条
	strcpy(Book[0].ch_num, "00");//数据库中现有5条记录
	strcpy(Book[0].ch_name,"微信，这么玩才赚钱");
	strcpy(Book[0].ch_author, "王易");
	strcpy(Book[0].ch_publisher,"机械工业出版社");
	strcpy(Book[1].ch_num,"01");
	strcpy(Book[1].ch_name,"微信营销解密");
	strcpy(Book[1].ch_author,"程小永");
	strcpy(Book[1].ch_publisher,"机械工业出版社");
	strcpy(Book[2].ch_num,"02");
	strcpy(Book[2].ch_name,"C++ Primer中文版（第5版）");
	strcpy(Book[2].ch_author,"（美）李普曼、拉乔伊");
	strcpy(Book[2].ch_publisher,"电子工业出版社");
	strcpy(Book[3].ch_num,"03");
	strcpy(Book[3].ch_name,"疯狂Android讲义");
	strcpy(Book[3].ch_author,"李刚");
	strcpy(Book[3].ch_publisher,"电子工业出版社");
	strcpy(Book[4].ch_num,"04");
	strcpy(Book[4].ch_name,"C程序设计 第四版");
	strcpy(Book[4].ch_author,"谭浩强");
	strcpy(Book[4].ch_publisher,"清华大学出版社");
	cout<<"------------------------图书管理系统---------------------"<<endl;
	cout<<"现库存图书有00-04号,图书信息有以下内容："<<endl;
	cout<<"图书编号---------图书名---------图书作者--------图书出版社"<<endl;
	int choice;
	int del_num;//删除信息
	int modify_num;//要修改信息
	int inspect_num;//查询信息
	bool xunhuan=true;
	while(xunhuan)
	{
		cout<<"当前库存"<<number<<"条图书信息"<<endl;
		cout<<"请选择您要操作的功能，对应功能选择按键："<<endl;
		cout<<"0-退出"<<endl;
		cout<<"1-添加"<<endl;
		cout<<"2-删除"<<endl;
		cout<<"3-修改"<<endl;
		cout<<"4-查询"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 0://退出
			cout<<"退出成功"<<endl;
			xunhuan=false;
			break;
		case 1://添加
			cout<<"请遵照上面信息排列输入新图书的信息:"<<endl;
			number++;
			cin>>Book[number].ch_num>>Book[number].ch_name>>Book[number].ch_author>>Book[number].ch_publisher;
			break;
		case 2://删除
			cout<<"要删除的第几条信息";
			cin>>del_num;
			number--;
			if(del_num>number)
				cout<<"没有该条信息"<<endl;
			else if(del_num==number)//删除最后一条
			{
				strcpy(Book[del_num-1].ch_author,"");
				strcpy(Book[del_num-1].ch_name,"");
				strcpy(Book[del_num-1].ch_publisher,"");
				strcpy(Book[del_num-1].ch_num,"");
			}
			else
			{
				for(int i=del_num-1;i<number;i++)
				{
					strcpy(Book[i].ch_author,Book[i+1].ch_author);
					strcpy(Book[i].ch_name,Book[i+1].ch_name);
					strcpy(Book[i].ch_publisher,Book[i+1].ch_publisher);
				}
			}
			break;
		case 3://修改
			cout<<"请输入要修改第几条信息";
			cin>>modify_num;
			if(modify_num>number)
				cout<<"没有该条信息"<<endl;
			else
			{
				cout<<"按次序输入新内容,如果部分修改，可将原信息原样输入"<<endl;
				cin>>Book[modify_num-1].ch_num>>Book[modify_num-1].ch_name>>Book[modify_num-1].ch_author>>Book[modify_num-1].ch_publisher;
			}
			break;
		case 4://查询
			cout<<"请输入要查询第几条信息:";
			cin>>inspect_num;
			cout<<Book[inspect_num].ch_num<<" "<<Book[inspect_num].ch_name<<" "<<Book[inspect_num].ch_author<<" "<<Book[inspect_num].ch_publisher<<endl;
			break;
		default:
			break;
		}
	}
	return 0;
}