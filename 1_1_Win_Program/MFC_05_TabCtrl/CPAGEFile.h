#pragma once


// CPAGEFile 对话框

class CPAGEFile : public CDialogEx
{
	DECLARE_DYNAMIC(CPAGEFile)

public:
	CPAGEFile(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPAGEFile();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
