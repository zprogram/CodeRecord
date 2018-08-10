#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

//综合练习3_设计一个简单的学生数据库类_读取文本存储

class student
{
private:
	string name;//姓名
	long num;//学号
	int age;//年龄
	char sex;//性别
	float score;//成绩
	int count;//计数
	ofstream fout;//输出流对象
	ifstream fin;//输入流对象
public:
	student();
	void new_record();//新记录
	void listnew();//罗列新记录
	void init();//初始化文件
	void quit();//退出
};
student::student()//构造函数
{
	name="";
	num=0;
	age=0;
	sex=' ';
	score=.0;
	count=0;
}
void student::init()
{
	fin.open("out.txt",ios::in);//打开输入文件
	if(fin.good())//被打开
	{
		cout<<"学生数据库中记录如下："<<endl;
		string temp;//临时字符串，读取字段
		for(int i=0;i<5;i++)
			fin>>temp;//读取字段
		fin>>name>>num>>age>>sex>>score;//读取记录
	}
	cout<<"姓名："<<name<<endl;//输出记录值
	cout<<"学号："<<num<<endl;
	cout<<"年龄："<<age<<endl;
	cout<<"性别："<<sex<<endl;
	cout<<"成绩："<<score<<endl;
}
void student::new_record()//新记录
{
	cout<<"输入姓名：";
	cin>>name;
	cout<<"输入学号：";
	cin>>num;
	cout<<"输入年龄：";
	cin>>age;
	cout<<"输入性别：";
	cin>>sex;
	cout<<"输入成绩：";
	cin>>score;
	count++;
}
void student::listnew()//罗列新记录
{
	if(count<=0)//没有记录
		cout<<"数据库中没有记录"<<endl;
	else
	{
		cout<<"姓名："<<name<<endl;
		cout<<"学号："<<num<<endl;
		cout<<"年龄："<<age<<endl;
		cout<<"性别："<<sex<<endl;
		cout<<"成绩："<<score<<endl;
	}
}
void student::quit()
{
	fout<<setiosflags(ios::left)<<setw(10);//设置输出格式
	fout<<name<<"	"<<num<<"	"<<age<<"	"<<sex<<"	"<<score<<'\n';//输出当前数据库内容
	fout.close();//关闭
}
void main()
{
	student _stu;//学生数据库对象
	char ch;//是否键入新记录
	bool flag=true;//继续输入
	_stu.init();//初始化文件
	while(flag)
	{
		cout<<"输入E或e以键入新记录：";
		cout<<endl<<"输入L或l以罗列新记录：";
		cout<<endl<<"输入Q或q退出程序：";
		cin>>ch;//获取
		switch(ch)//判断
		{
		case 'e':
		case 'E':
			_stu.new_record();//新记录
			break;
		case 'l':
		case 'L':
			_stu.listnew();//罗列新记录
			break;
		case 'q':
		case 'Q':
			_stu.quit();//退出
			flag=false;//跳出循环
			break;
		}
	}
}