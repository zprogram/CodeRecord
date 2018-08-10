#include <iostream>
using namespace std;

int array_039[10]={0,1,2,3,4,5,6,7,8,9};

void binary_search(int left,int right,int value)
{
	int search_index;
	search_index=(left+right)/2;//二分
	if(array_039[search_index]==value)//如果等于二分点值
		cout<<"元素"<<value<<"位于第"<<search_index<<"位"<<endl;
	else if(value>array_039[search_index])//大于，往右边移
		binary_search(search_index+1,right,value);
	else if(value<array_039[search_index])//小于，往左边移
		binary_search(left,search_index-1,value);
	else
		return;
}

int main()
{
	int temp;
	cout<<"输入你想要找的元素值：";
	cin>>temp;
	binary_search(0,9,temp);

	return 0;
}
