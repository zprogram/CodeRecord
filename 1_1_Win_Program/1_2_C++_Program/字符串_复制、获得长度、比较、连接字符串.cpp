#include <iostream>
using namespace std;

int main()
{


	//复制一个字符串（strcpy()）
	char str1[] = "Hello World";
	char str2[30];
	strcpy(str2, str1);

	//获得字符串长度（strlen()）
	char str[] = "HelloWorld";
	cout << "str的长度为:" << strlen(str) << endl;

	//字符串的比较（strcmp()）
	//int __cdecl strcmp(
	//	_In_z_ char const* _Str1,
	//	_In_z_ char const* _Str2
	//	);
	// 如果返回值为0   string1 等于 string2
	// 如果返回值大于0 string1 大于 string2
	// 如果返回值小于0 string1 小于 string2
	char str3[] = "HelloWorld";
	char str4[] = "Hello World";
	int result;
	result = strcmp(str3, str4);

	if (result < 0)
		cout << "str3小于str4" << endl;
	else if (result>0)
		cout << "str3大于str4" << endl;
	else
		cout << "str3等于str4" << endl;

	// 连接两个字符串
	char str5[100]="Hello";//一定要给str1的大小赋值，否则会越界
	char str6[]=" World";

	strcat(str5,str6);
	cout<<str1<<endl;
	
	return 0;
}