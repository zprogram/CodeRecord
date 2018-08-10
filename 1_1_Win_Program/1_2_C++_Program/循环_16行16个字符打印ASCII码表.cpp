#include <iostream>
using namespace std;

int main()
{
    int i =0;
    for(int rows = 0; rows < 16; rows++)
    {

        i = rows;                             // 16行的字符
        while(i <= 127)
        {
			switch(i)
			{
			case 7://震铃
				cout<<i<<"="<<"\\a"<<" | ";
				break;
			case 8://退格
				cout<<i<<"="<<"\\b"<<" | ";
				break;
			case 9://水平制表符
				cout<<i<<"="<<"\\t"<<" | ";
				break;
			case 10://换行
				cout<<i<<"="<<"\\n"<<" | ";
				break;
			case 11://竖直制表符
				cout<<i<<"="<<"\\v"<<" | ";
				break;
			case 12://换页
				cout<<i<<"="<<"\\f"<<" | ";
				break;
			case 13://回车
				cout<<i<<"="<<"\\r"<<" | ";
				break;
			default:
				cout<<i<<"="<<char(i)<<" | ";  //将数字转换成字符输出，用了char函数
				break;
			}

            i+=16;//每隔16个另起一列
        }

        cout<<endl;
    }

    return 0;
}