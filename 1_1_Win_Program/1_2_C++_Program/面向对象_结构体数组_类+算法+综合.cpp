// 代码重点 结构体数组+结构体赋值
// 类+算法+综合
// 实现入学登记系统，对学生的各类信息进行记录，如姓名、性别、年龄、籍贯、手机号、专业及班级号等。
// 如果当前输入的信息已存在，则输出提示信息。
// 最大记录100个学生的信息


#include <iostream>
#include <string>
using namespace std;

struct stu_info//学生信息
{
	string name;            //姓名
	int sex;                //性别，0-女，1-男
	int age;                //年龄
	string hometown;        //籍贯
	string mobile_number;   //手机号
	int major;              //专业
	int class_num;          //班级号
};
class student
{
public:
	student();             //构造函数
	void Print();          //打印学院情况
	void Input();          //输入信息
	bool Certain();        //该条信息是否已存在
	void Register();       //登记信息
private:
	stu_info _stu[100];    //系统只能包括100人的信息
	stu_info temp;         //临时信息
	int num;               //总共几个人
};
student::student()
{
	num=0;                  //初始只有0个人
}
void student::Print()       //打印信息
{
	cout<<"本系统只登记电子信息学院的学生信息"<<endl;
	cout<<"学院下的专业分别为："<<endl;
	cout<<"  0-信号与信息处理"<<endl;
	cout<<"  1-通信原理"<<endl;
	cout<<"  2-电路系统"<<endl;
	cout<<"每个专业下分别设有2个班，分别为00和01"<<endl;
}
void student::Input()//输入信息
{
	cout<<"请按照下面提示，在右面输入信息："<<endl;
	cout<<"姓名:"; cin>>temp.name;
	cout<<"性别:"; cin>>temp.sex;
	cout<<"年龄:"; cin>>temp.age;
	cout<<"籍贯:"; cin>>temp.hometown;
	cout<<"手机号:"; cin>>temp.mobile_number;
	cout<<"专业编号:"; cin>>temp.major;//输入专业
	cout<<"班级编号:"; cin>>temp.class_num;//输入班级号
}
void student::Register()//登记信息
{
	if(Certain()==true)//当前信息还没有
	{
		if(num>99)
			cout<<"登记系统已满，下午再来，谢谢"<<endl;
		else
		{
			_stu[num]=temp;//赋值
			cout<<"第"<<num+1<<"条信息成功登记"<<endl;
		}
		num++;//人数加1
	}
	else
		cout<<"您已经登记过，无需重复"<<endl;
}
bool student::Certain()//是否
{
	for(int i=0;i<num;i++)//与所有有效信息比较
	{
		if(_stu[i].age==temp.age && _stu[i].class_num==temp.class_num 
			&& _stu[i].hometown==temp.hometown
			&& _stu[i].major==temp.major 
			&& _stu[i].mobile_number==temp.mobile_number
			&& _stu[i].name==temp.name && _stu[i].sex==temp.sex)//已存在
			return false;
	}
	return true;
}
void main()
{
	student a;       //学生类对象
	int ch;          //选择
	a.Print();       //打印注意事项
	do
	{
	
		a.Input();   //输入信息
		a.Register();//登记	
		cout<<"继续输入吗：0-是，1-否"<<endl;
		cin>>ch;
	}while(ch==0);



}