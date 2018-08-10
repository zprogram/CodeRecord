#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

class CDiffRule
{
public:
	CDiffRule();


	// ��Ҫ�Աȹ����ܺ���
	int DiffRuleProcess(char * nPara1,char * nPara2);
	// �ж������ļ��Ƿ����
	bool ifstreamProcess(char* nFile_Name);
	// ��ȡ�ж��������ɵ��ļ�������
	bool TargetRule(char* nFile_Name);
	// ��ȡ���ػ������ɵ��ļ�������
	bool DiffRule(char* nFile_Name);
	// vector�������
	bool vecFileProcess();
	vector<int>vecIndex;
	//�Ա�Ŀ��Ŀ¼
	vector <string> vecTatgetRule;
	//��������
	vector <string> vecDiffRule;
	~CDiffRule();
};

