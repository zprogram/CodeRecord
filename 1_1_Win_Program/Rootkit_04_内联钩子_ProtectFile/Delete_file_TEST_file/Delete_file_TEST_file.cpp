// Delete_file_TEST_file.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <process.h>
using namespace std;

int main()
{

	std::cout << "The process id is: " << _getpid() << std::endl;

	system("pause");

	HANDLE hFILE = CreateFileW(L"TestFileName.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFILE == INVALID_HANDLE_VALUE)
	{
		printf("CreateFile error\n");
	}
	printf("CreateFileW function run ends , enter any quit program\n");
	system("pause");
    return 0;
}

