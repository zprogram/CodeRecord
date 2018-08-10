// 函数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdlib.h"


int sort(char arr[])
{
	int len = sizeof(arr);
        for(int i= 0 ; i < len-1; i ++)
        {
           for(int j = 0 ; j<len-1-i; j++)
           {
               if(arr[j]<arr[j+1])
               {
                  char temp;
                   temp = arr[j];
                   arr[j] = arr[j+1];
                   arr[j+1] = temp;
               }   
           }

        }
		return 0;
}


int main()
{
        char arr[5] = {'5','4','1','6'};
        sort(arr);


	system("pause");

	return 0;
}