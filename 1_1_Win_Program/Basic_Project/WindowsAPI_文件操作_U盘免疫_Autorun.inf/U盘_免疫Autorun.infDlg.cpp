
// U盘_免疫Autorun.infDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "U盘_免疫Autorun.inf.h"
#include "U盘_免疫Autorun.infDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CU盘_免疫AutoruninfDlg 对话框



VOID CU盘_免疫AutoruninfDlg::InitComboDriver()
{

	WCHAR szDriverString[MAXBYTE] = { 0 };
	DWORD iNum = 0;
	DWORD dwRet = 0;
	WCHAR szRoot[4] = { 0 };

	SetDlgItemText(IDC_COMBO_DRIVER, _T("请选择欲免疫的盘符..."));
	// 获取本地逻辑磁盘函数
	dwRet = GetLogicalDriveStrings(MAXBYTE, szDriverString);

	while (iNum < dwRet)
	{
		/**  获取每个磁盘的盘符名 C:\\ D:\\ E:\\ F:\\ **/
		wcsncpy_s(szRoot, &szDriverString[iNum], 3);
		m_ComboDriver.AddString(szRoot);
		iNum += 4;
	}

	return VOID();
}

CU盘_免疫AutoruninfDlg::CU盘_免疫AutoruninfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_U_AUTORUNINF_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CU盘_免疫AutoruninfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_DRIVER, m_ComboDriver);
}

BEGIN_MESSAGE_MAP(CU盘_免疫AutoruninfDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_IMMUNITY, &CU盘_免疫AutoruninfDlg::OnBtnImmunity)
	ON_BN_CLICKED(IDC_BTN_CANCEL, &CU盘_免疫AutoruninfDlg::OnBtnCancel)
END_MESSAGE_MAP()


// CU盘_免疫AutoruninfDlg 消息处理程序

BOOL CU盘_免疫AutoruninfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitComboDriver();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CU盘_免疫AutoruninfDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CU盘_免疫AutoruninfDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CU盘_免疫AutoruninfDlg::OnBtnImmunity()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	WCHAR szPath[MAX_PATH] = { 0 };

	GetDlgItemText(IDC_COMBO_DRIVER, szPath, MAX_PATH);

	// 创建autorun.inf文件夹
	wcscat_s(szPath, 255,AUTORUN);
	BOOL bRet = CreateDirectory(szPath, NULL);
	if (!bRet)
	{
		MessageBox(L"无法免疫该盘符！可能已经免疫，或者该磁盘为不可写状态！", MB_OK, NULL);
		return;
	}

	// 创建无法删除的用来进行免疫的文件夹
	wcscat_s(szPath,255, IMMUNITY);
	bRet = CreateDirectory(szPath, NULL);
	if (!bRet)
	{
		MessageBox(L"无法免疫该盘符！可能已经免疫，或者该磁盘为不可写状态！", MB_OK,NULL);
		return;
	}
	MessageBox(L"免疫该盘符成功！", MB_OK, NULL);

}


void CU盘_免疫AutoruninfDlg::OnBtnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	WCHAR szPath[MAX_PATH] = { 0 };

	GetDlgItemText(IDC_COMBO_DRIVER, szPath, MAX_PATH);
	wcscat_s(szPath,255, AUTORUN);
	wcscat_s(szPath, 255,IMMUNITY);
	RemoveDirectory(szPath);

	ZeroMemory(szPath, MAX_PATH);

	GetDlgItemText(IDC_COMBO_DRIVER, szPath, MAX_PATH);
	wcscat_s(szPath,255, AUTORUN);
	RemoveDirectory(szPath);


}
