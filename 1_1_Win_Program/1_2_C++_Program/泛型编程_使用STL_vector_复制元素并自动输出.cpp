#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//在标准模板库的算法中，有一个专门的函数为copy()。
//它以前向遍历的方式访问源序列的元素，同时赋值给目标序列。
//本示例演示复制元素，并自动输出图书的字符。


void main()
{
	char ch[12]="Hello World";
	vector<char> v_src(12,' '),v_dst(12 ,' ');//源向量和目标向量
	cout<<"图书样本内容：";
	for(int i=0;i<12;i++)
	{
		v_src.at(i)=ch[i];//赋值
		cout<<ch[i];//输出源内容
	}
	cout<<endl;
	copy(v_src.begin(),v_src.end(),v_dst.begin());//把v_src复制到v_dst
	cout<<"经过印刷，图书内容为：";
	for(int i=0;i<12;i++)
		cout<<v_dst.at(i);//输出目标内容
	cout<<endl;
}