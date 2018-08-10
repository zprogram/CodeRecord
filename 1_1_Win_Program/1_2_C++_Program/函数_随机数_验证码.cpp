#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void generate_lower()
{
	char lower;
	int lower_index;
	lower_index=1+(int)(26.0*rand()/(RAND_MAX+1.0));
	lower=char(lower_index+96);
	cout<<lower;
}
void generate_upper()
{
	char upper;
	int upper_index;
	upper_index=1+(int)(26.0*rand()/(RAND_MAX+1.0));
	upper=char(64+upper_index);
	cout<<upper;
}
void generate_number()
{
	int number;
	number=0+(int)(9.0*rand()/(RAND_MAX+0.0));
	cout<<number;
}
int main()
{
	srand((int)time(0));
	int num;
	int upper;
	int lower;
	int number;
	while(1)
	{
		cout<<"请输入验证码的位数：";
		cin>>num;
		cout<<"在这"<<num<<"位验证码中，需要大写字母、小写字母、数字各几位，请输入";
		cin>>upper>>lower>>number;
		while(upper)
		{
			generate_upper();
			upper--;
		}
		while(lower)
		{
			generate_lower();
			lower--;
		}
		while(number)
		{
			generate_number();
			number--;
		}
		cout<<endl<<"是否继续产生随机验证码?"<<endl;
		cout<<"1.是 2.否"<<endl;
		int y;
		cin>>y;
		cout<<endl;
		if(y==1)
		{}
		if(y==2)
		{
			cout<<"退出系统"<<endl;
			break;
		}
	}
	return 0;
}