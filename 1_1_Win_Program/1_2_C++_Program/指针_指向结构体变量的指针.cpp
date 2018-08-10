#include <iostream>
#include <string>
using namespace std;


//指向结构体变量的指针


struct newtype
{
	int a;
	char ch;
	string str;
};
int main()
{
	newtype *new_type_point, new_type; //定义结构体变量new_type和其指针变量new_type_point
	new_type_point=&new_type;          //使new_type_point指向new_type变量
	new_type.a=1;                      //初始化
	new_type.ch='p';
	new_type.str="jkdas";
	                                   //获取new_type中前两个成员的值
	cout<<(*new_type_point).a<<endl;   //方式1：指向结构体成员a
	cout<<new_type_point->ch<<endl;    //方式2：指向结构体成员a
	//new_type_point.a;//错误形式
	string *str_point;
	str_point=&new_type.str;           //指向结构体中元素ch的指针
	cout<<*str_point<<endl;            
	return 0;
}