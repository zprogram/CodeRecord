// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")
#include <windows.h>
#include <lmaccess.h>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
	bool Find(int target, vector<vector<int>> array) {
		int rlength = array.size();//行长度
		int clength = array[0].size();//列长度
		int row = 0;//行指针
		int col = clength - 1;//列指针
		while (row < rlength&&col >= 0) {
			if (target == array[row][col]) {
				return true;
			}
			else if (array[row][col] > target) {
				col--;
			}
			else {
				row++;
			}
		}
		return false;
	}
};



int wmain(int argc, wchar_t *argv[])
{
	Solution s;

	vector<vector<int>> test;
	vector<int> v;
	int n, temp;

	test.clear();

	//输入
	for (int i = 0; i < 2; i++) {
		v.clear(); //每次记得clear:)
		for (int j = 0; j < 3; j++)
		{
			cin >> temp;
			v.push_back(temp);
		}
		test.push_back(v);
	}



	s.Find(6, test);

	
}