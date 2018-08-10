#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <assert.h>
using namespace std;


//开发一个完整的学生数据管理系统，每次登记学生信息时，将该信息写入文件stu_info.txt中，读取信息时，打开该文件显示到屏幕。

// readfile()  读取文件
// writefile() 写入文件
// insert()    写入学生信息
// display()   读取学生信息
// mainpage()  主页面


// 测试信息
// stu_info.txt
//ada	20145	25	f	98	97	92	84
//john	20146	28	f	85	98	97	95
//eva	2019	26	m	87	85	96	82
//star	201485	19	f	85	97	95	84
//Aaron	201496	24	m	96	85	74	92
//star	20148	25	f	58	47	96	85
//Jim	2014965	23	m	96	54	87	95
//Jin	2014879	28	m	85	87	81	69
//Heng	201435	25	f	89	48	58	69
//Tom	20136	25	m	25	14	85	74



struct score  //成绩结构体 
{   
	int Math;   //数学
	int Physics;   //物理
	int English;   //英语
	int Computer;   //计算机
}; 
class student
{
private:
	string name;//姓名
	long num;//学号
	int age;//年龄
	char sex;//性别
	int count;//计数
	score s;//成绩
	ofstream fout;//输出流对象
	ifstream fin;//输入流对象
public:
	student();//构造函数
	~student();//析构函数
	void mainpage();//主页面
	void readfile();//读入文件
	void writefile();//写出文件
	void insert();//输入学生信息
	void display();//读取
};
void student::readfile()
{
	cout<<"姓名	学号	年龄	性别	数学	物理	英语	计算机"<<endl;
	fin.open("stu_info.txt",ios::in|ios::out);//打开输入文件
	if(fin.good())//被打开
	{
		while(!fin.eof())//没到文件末尾
		{
			fin>>name>>num>>age>>sex>>s.Math>>s.Physics>>s.English>>s.Computer;//读取记录
			cout<<name<<"	"<<num<<"	"<<age<<"	"<<sex<<"	";//输出屏幕
			cout<<s.Math<<"	"<<s.Physics<<"	"<<s.English<<"	"<<s.Computer<<endl;	
		}
	}
	fin.close();//关闭	
}
void student::writefile()
{
	fout.open("stu_info.txt",ios::out|ios::in|ios::ate);
	if(fout.good())
	{
		fout<<'\n'<<name<<"	"<<num<<"	"<<age<<"	"<<sex<<"	";
		fout<<s.Math<<"	"<<s.Physics<<"	"<<s.English<<"	"<<s.Computer;//写出
	}
	cout<<"写入成功"<<endl;
	fout.close();//关闭
}
student::student()//构造函数
{
	name="";//初始化各变量
	num=0;
	age=0;
	sex=' ';
	count=0;	
	s.Math=0;
	s.Physics=0;
	s.English=0;
	s.Computer=0;
}
student::~student()
{}
void student::insert()//新记录
{
	char n;
	do
	{
		cout<<"输入姓名：";
		cin>>name;
		cout<<"输入学号：";
		cin>>num;
		cout<<"输入年龄：";
		cin>>age;
		cout<<"输入性别：";
		cin>>sex;
		cout<<"输入数学成绩：";
		cin>>s.Math;
		cout<<"输入物理成绩：";
		cin>>s.Physics;
		cout<<"输入英语成绩：";
		cin>>s.English;
		cout<<"输入计算机成绩：";
		cin>>s.Computer;
		writefile();//写出学生信息
		count++;
		cout<<"继续输入?(Y/N)";
		cin>>n;
	}while(n=='Y'||n=='y');
	system("cls");//清屏
	mainpage();//主页面
}
void student::display()
{
	readfile();
	mainpage();//主页面
}
void student::mainpage()
{
	int choose;//选择
	cout<<"\n\n";   
	cout<<"\t\t\t学生数据管理系统V1.0\n";   
	cout<<"\t    ";   
	for(int i=0;i<47;i++)   
		cout<<"*";   
	cout<<"\n";    
	cout<<"\t    *   1.录入.\t\t\t\t          *\n";    
	cout<<"\t    *   2.读取.\t\t\t\t          *\n";   
	cout<<"\t    *   other.退出.\t\t\t          *\n";   
	cout<<"\t    ";   
	for(int i=0;i<47;i++)   
		cout<<"*";   
	cout<<"\n\n"; 
	cout<<"请选择你要进行的操作: ";   
	cin>>choose;//输入选择
	switch(choose)   
	{   
	case 1: insert();   //录入
		break;   
	case 2: display();//读取
		break;
	default: exit(-1);   
	}   
}
void main()
{
	student _stu;//学生数据库对象
	_stu.mainpage();//显示主页面
}