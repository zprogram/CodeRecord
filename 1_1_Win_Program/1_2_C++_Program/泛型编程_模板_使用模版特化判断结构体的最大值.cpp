#include <iostream>
using namespace std;

// 使用模版特化判断结构体的最大值


struct data_base
{
	int a;//整型
	char ch;//字符型
};
template<class T> T mymax(const T t1,const T t2)
{
	return t1<t2?t2:t1;//返回最大值
}
const struct data_base mymax(const struct data_base t1,const struct data_base t2)
{
	if(t1.a>t2.a)        //第1个的a大
		return t1;       //返回第1个
	else if(t1.a==t2.a)  //a相等
	{
		if(t1.ch>=t2.ch)//判断第2个，t1不小于t2
			return t1;  //返回第1个
		else            //t1小于t2
			return t2;  //返回第2个
	}
	else//第2个的a大
		return t2;//返回第2个
}
void main()
{
	data_base a,b;
	a.a=4;a.ch='c';
	b.a=59;b.ch='t';
	cout<<mymax(2,15)<<" ";
	cout<<mymax('b','x')<<" ";
	cout<<mymax(true,false)<<" ";
	cout<<"<"<<mymax(a,b).a<<","<<mymax(a,b).ch<<")"<<endl;  // 结构体比大小
}