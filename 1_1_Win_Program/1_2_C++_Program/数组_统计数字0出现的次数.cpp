#include <iostream>
#include <string>
using namespace std;

int main()
{
	cout<<"请输入一串数字，不能有空格等非数字字符"<<endl;
	string str;
	int count_0=0;//0出现的次数
	cin>>str;//输入
	cout<<"数字0出现的次数为:";
	for(int i=0;i<str.length();i++)//判断
	{
		if(str[i]=='0')//如果等于0
			count_0++;
		else
		{}
	}

	cout<<count_0<<endl;

	return 0;
}