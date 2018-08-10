#include <iostream>
#include <climits>
#include <cfloat>
using namespace std;

int main()
{
	int i;//基本整型
	short j;//短整型
	long k;//长整型
	float ii;//单精度型
	double jj;//双精度型
	long double kk;//扩展双精度型

	cout<<"i:("<<INT_MIN<<","<<INT_MAX<<")"<<endl;
	cout<<"j:("<<SHRT_MIN<<","<<SHRT_MAX<<")"<<endl;
	cout<<"k:("<<LONG_MIN<<","<<LONG_MAX<<")"<<endl;
	cout<<"ii:("<<FLT_MIN<<","<<FLT_MAX<<")"<<endl;
	cout<<"jj:("<<DBL_MIN<<","<<DBL_MAX<<")"<<endl;
	cout<<"kk:("<<LDBL_MIN<<","<<LDBL_MAX<<")"<<endl;

	return 0;
} 