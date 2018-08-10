
// MFC配置端Dlg.h : 头文件
//

#pragma once


// CMFC配置端Dlg 对话框
class CMFC配置端Dlg : public CDialogEx
{
// 构造
public:
	CMFC配置端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_szIpStr;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnChangePE();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString m_szPortStr;
	CString m_szOtherStr;
	afx_msg void OnBnChangeResource();

	// 修改PE的文件
	CString strPath, strEXE, strResult;
	// 生成状态识别
    // 1 exe
	// 2 dll
	int BuildFlag;

	afx_msg void OnBuild_DLL();
	CString m_usage_method;
	afx_msg void Builx64EXE();
	afx_msg void Builx64DLL();
};
