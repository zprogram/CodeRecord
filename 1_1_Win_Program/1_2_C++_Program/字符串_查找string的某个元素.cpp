#include <iostream>
#include <string>
using namespace std;

//查找string的某个元素
int main()
{
	string str="Hello;;";
	char ch=';';
	cout << str<< "长度" << str.length()<< "位" << endl;
	cout<<"元素ch位于字符串str的第"<<str.find(ch)<<"位"<<endl;                                         //(1)从pos位置的位置开始从前向后查找字符C在当前字符串中的位置，默认pos的值为0.

	cout<<"从pos位置开始从前向后查找字符c在当前字符串中第一个不匹配的字符位置 "<<str.find_first_not_of(ch)<<endl; //(2)从pos位置开始从前向后查找字符c在当前字符串中第一个不匹配的字符位置
	
	cout<<"从pos位置开始从前向后查找字符c在当前字符串中第一次出现的位置 "<<str.find_first_of(ch)<<endl; //(3)从pos位置开始从前向后查找字符c在当前字符串中第一次出现的位置
	
	cout<<"从pos位置开始从后向前查找字符c在当前字符串中第一个不匹配的字符位置 "<<str.find_last_not_of(ch)<<endl;   //(4)从pos位置开始从后向前查找字符c在当前字符串中第一个不匹配的字符位置
	
	cout<<"从pos位置开始从后向前查找字符c在当前字符串中第一次出现的位置 "<<str.find_last_of(ch)<<endl; //(5)从pos位置开始从后向前查找字符c在当前字符串中第一次出现的位置
	
	cout<<"从pos位置开始从后往前查找字符c在当前字符串中的位置 "<<str.rfind(ch)<<endl;//多种方式     //(6)从pos位置开始从后往前查找字符c在当前字符串中的位置。
	
	return 0;
}