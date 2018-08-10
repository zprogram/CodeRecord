#include <iostream>
using namespace std;

//	实例085  寻找地址（指针加减法）
int main()
{
	int num[]={0,1,2,3,4,5,6};
	int *ptr;
	ptr=&num[0];
	cout<<ptr<<" "<<*(ptr++)<<endl;    //注意：这里输出0的时候，地址往上加了一位，输出就变成了6
	cout<<ptr+5<<" "<<*(ptr+5)<<endl;

	return 0;
}