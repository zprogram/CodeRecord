#include <iostream>
using namespace std;

int level(char ch)
{
	switch(ch)
	{
	case '!':
		return 2;
		break;
	case '*':
		return 3;
		break;
	case '/':
		return 3;
		break;
	case '%':
		return 3;
		break;
	case '+':
		return 4;
		break;
	case '-':
		return 4;
		break;
	case '=':
		return 5;
		break;
	default:
		return -1;
		break;
	}
}

int main()
{
	char symbol[3];
	int value[3];
	cout<<"从!、*、/、%、+、-、=运算符中选择3个参与算术运算"<<endl;
	cin>>symbol[0]>>symbol[1]>>symbol[2];
    //把符号问题转换成数字问题
	value[0]=level(symbol[0]);
	value[1]=level(symbol[1]);
	value[2]=level(symbol[2]);


	if((value[0]==-1) || (value[1]==-1) || (value[2]==-1))//只要有一个返回负数
		cout<<"库中没有输入的运算符"<<endl;
	else
	{
		//从大到小排序
		for (int i = 0;i < 3; i++)
		{
			for (int j = i; j<3;j++)
			{
				if(value[i]>value[j])//如果前一个大于后一个,开始交换
				{
					//交换
					char temp;
					temp=symbol[i];
					symbol[i]=symbol[j];
					symbol[j]=temp;
				}
			}
		}
		cout<<"依次进入运算的顺序为："<<endl;
		for(int k=0;k<3;k++)
			cout<<symbol[k]<<endl;
	}

	return 0;
}