// 冒泡排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{

	int arr[] = { 8, 5, 3, 1, 4, 7, 9, 6, 0, 2 };
	//int len = _countof(arr);
	//第二种写法
	int len = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < len - 1; i++)  //每次选出最大的放在数组最后，共选择九次
	{
		for (int j = 0; j < len - 1 - i; j++) /*控制怎么选出最大的！通过两两比较，把大的交换到后面，已经排好的元素不管他*/
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}

		}
	}
	return 0;
}

