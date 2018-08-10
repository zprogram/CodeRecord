#include <iostream>
#include <string>
using namespace std;

//比较两个string字符串
int main()
{
	string str1="Hello";
	string str2="World";
	string str3="HELLO";
	int compare_result;
	if(str1!=str2)//方式1
		cout<<"str1不等于str2"<<endl;

	if(bool(compare_result=str3.compare(str1)))//不相等（方式2）
		cout<<"str1不等于str3"<<endl;
	return 0;
}