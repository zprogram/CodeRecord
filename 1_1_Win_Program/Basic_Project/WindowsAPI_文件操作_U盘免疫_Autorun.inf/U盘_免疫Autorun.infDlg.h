
// U盘_免疫Autorun.infDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// 创建的目录
#define AUTORUN     L"autorun.inf"
// 创建的无法删除的目录
#define IMMUNITY    L"\\Immunity...\\"

// CU盘_免疫AutoruninfDlg 对话框
class CU盘_免疫AutoruninfDlg : public CDialogEx
{
// 构造
public:

	VOID InitComboDriver();  //遍历磁盘
	CU盘_免疫AutoruninfDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_U_AUTORUNINF_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ComboDriver;
	afx_msg void OnBtnImmunity();
	afx_msg void OnBtnCancel();
};
