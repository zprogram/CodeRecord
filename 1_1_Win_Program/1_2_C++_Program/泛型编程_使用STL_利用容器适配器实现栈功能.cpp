#include <iostream>  
#include <stack>  
using namespace std;  

//利用容器适配器实现栈功能

void main()  
{  
	stack<int> st;

	st.push(1);//向栈内压入元素
	st.push(2);
	st.push(3);
	st.push(4);
	while(!st.empty())//没到末尾
	{
		cout<<st.top()<<" ";//输出
		st.pop();//pop掉
	}
	cout<<endl;
}