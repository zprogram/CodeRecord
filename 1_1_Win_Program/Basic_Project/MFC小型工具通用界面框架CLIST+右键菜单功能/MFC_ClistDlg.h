
// MFC_ClistDlg.h: 头文件
//

#pragma once


// CMFCClistDlg 对话框
class CMFCClistDlg : public CDialogEx
{
// 构造
public:
	CMFCClistDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_CLIST_DIALOG };
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
	CListCtrl m_List_xxx;
	int GUI_InitList(void);
	void GUI_ShowMessage(bool bIsOK, CString strMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void GUI_Dir_Delete();
	afx_msg void GUI_Dir_DeleteALL_Items();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void GUI_Add_Check_Dir();
};
