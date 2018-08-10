#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

class CopyFileToDir
{
public:
	CopyFileToDir();

	bool ReadTXTFile_GetPath(char * PathText, char *Path);
	//�Ա�Ŀ��Ŀ¼
	vector <string> vecTatgetPath;

	~CopyFileToDir();
};

