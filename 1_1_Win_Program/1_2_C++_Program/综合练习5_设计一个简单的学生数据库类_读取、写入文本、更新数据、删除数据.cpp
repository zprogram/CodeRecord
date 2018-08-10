#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <assert.h>
using namespace std;


// 基于之前基础上加入两个新的功能，更新数据和删除数据。
// 对应的数据字节大小需要一致，否则在进行读取操作时会进入无限循环。

//测试数据
// stu_info.txt
//张三	20145	25	f	98	97	92	80
//李立	20136	25	4	54	45	78	45
//王五	20148	19	f	85	97	95	84
//小红	20135	25	f	52	47	58	78
//小明	20139	23	m	96	54	87	95
//小王	20142	28	m	85	87	81	69
//xiaohong	2018	20	f	100	20	3	45


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
public:
	student();
	~student();
	void mainpage();//主页面
	void readfile();//读入文件
	void writefile();//写出文件
	void insert();//输入学生信息
	void update();//更新
	void del();//删除
	void display();//读取
};
void student::update()
{
	ifstream fin;
	ofstream fout;
	bool flag=false;//是否找到对应项
	streampos ps_ex=0;//前一行末尾位置
	streampos ps_every=0;//每一行有几个位置单位
	fin.open("stu_info.txt",ios::in|ios::out);//打开输入文件
	char ch;
	if(!fin.good())
		return;
	do
	{
		int n;
		cout<<"请输入您要更新的学生信息，其学号为："<<endl;
		cin>>num;
		while(!fin.eof())
		{
			long temp;//临时变量
			fin>>name>>temp>>age>>sex>>s.Math>>s.Physics>>s.English>>s.Computer;//读取记录
			ps_every=fin.tellg()-ps_ex;//计算每行的位置单位个数
			ps_ex=fin.tellg();//获取前一行的末尾位置
			if(temp==num)//相同
			{
				flag=true;//找到
				fin.close();
				fout.open("stu_info.txt",ios::out|ios::in);
				if(!fout.good())
					return;
				fout.seekp(ps_ex-ps_every,ios::beg);//移动文件指针
				cout<<"请依次输入下列需更新的项目,不需要更新的请原样输入："<<endl;
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
				fout<<"\n"<<name<<"	"<<num<<"	"<<age<<"	"<<sex<<"	";
				fout<<s.Math<<"	"<<s.Physics<<"	"<<s.English<<"	"<<s.Computer;//写出
				cout<<"更新成功"<<endl;
				break;
			}
		}
		if(flag==false)
			cout<<"没有找到符合选项"<<endl;
		cout<<"继续更新?(Y/N)";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	fout.close();//关闭
	system("cls");//清屏
	mainpage();//主页面
}
void student::del()
{
	ifstream fin;
	ofstream fout;
	bool flag=false;
	streampos ps_ex=0;//前一行末尾位置
	streampos ps_every=0;//每一行有几个位置单位
	fin.open("stu_info.txt",ios::in|ios::out);//打开输入文件
	char ch;
	if(!fin.good())
		return;
	do
	{
		int n;
		cout<<"请输入您要删除的学生信息，其学号为："<<endl;
		cin>>num;
		while(!fin.eof())
		{
			long temp;//临时变量
			fin>>name>>temp>>age>>sex>>s.Math>>s.Physics>>s.English>>s.Computer;//读取记录
			ps_every=fin.tellg()-ps_ex;//计算每行的位置单位个数
			ps_ex=fin.tellg();//获取前一行的末尾位置
			if(temp==num)//相同
			{
				flag=true;
				fin.close();
				fout.open("stu_info.txt",ios::out|ios::in);
				if(!fout.good())
					return;
				fout.seekp(ps_ex-ps_every,ios::beg);//移动文件指针
				streampos ps=fout.tellp();//获取当前位置
				while(ps!=ps_ex)
				{
					fout<<" ";
					ps=fout.tellp();//再次获取
				}
				cout<<"删除成功"<<endl;
				break;
			}
		}
		if(flag==false)
			cout<<"没有找到对应项"<<endl;
		cout<<"继续删除?(Y/N)";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	fout.close();//关闭
	system("cls");//清屏
	mainpage();//主页面
}
void student::readfile()
{
	ifstream fin;//输入流对象
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
	ofstream fout;//输出流对象
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
	cout<<"\t\t\t学生数据管理系统V2.0\n";   
	cout<<"\t    ";   
	for(int i=0;i<47;i++)   
		cout<<"*";   
	cout<<"\n";    
	cout<<"\t    *   1.录入.\t\t\t\t          *\n";    
	cout<<"\t    *   2.读取.\t\t\t\t          *\n"; 
	cout<<"\t    *   3.更新.\t\t\t\t          *\n";     
	cout<<"\t    *   4.删除.\t\t\t\t          *\n";   
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
	case 3: update();  //更新
		break;     
	case 4: del();//删除
		break;
	default: exit(-1);   
	}   
}
void main()
{
	student _stu;//学生数据库对象
	_stu.mainpage();//显示主页面
}