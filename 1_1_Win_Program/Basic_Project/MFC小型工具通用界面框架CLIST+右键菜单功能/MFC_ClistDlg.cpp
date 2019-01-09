
// MFC_ClistDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_Clist.h"
#include "MFC_ClistDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


/////////////////////////////////////////// 列表控件
typedef struct
{
	WCHAR	*title;           //列表的名称
	int		nWidth;           //列表的宽度
}COLUMNSTRUCT;

COLUMNSTRUCT g_Column_Message_Data[] =
{
	{ _T("信息类型"),		80	},
	{ _T("时间"),			100	 },
	{ _T("信息内容"),	    300	}
};
//变量声明
int g_Column_Message_Count = 3; //列表的个数
int g_Column_Message_Width = 0;  //列总宽度，初始化为0。在后面的函数中会赋值

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCClistDlg 对话框



CMFCClistDlg::CMFCClistDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_CLIST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List_xxx);
}

BEGIN_MESSAGE_MAP(CMFCClistDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(ID_S_32771, &CMFCClistDlg::GUI_Dir_Delete)
	ON_COMMAND(ID_S_32772, &CMFCClistDlg::GUI_Dir_DeleteALL_Items)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CMFCClistDlg::OnNMRClickList1)
	ON_COMMAND(ID_S_32773, &CMFCClistDlg::GUI_Add_Check_Dir)
END_MESSAGE_MAP()


// CMFCClistDlg 消息处理程序

BOOL CMFCClistDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GUI_InitList();

	GUI_ShowMessage(true, L"mesage");
	GUI_ShowMessage(true, L"mesage1");



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCClistDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCClistDlg::OnPaint()
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
HCURSOR CMFCClistDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMFCClistDlg::GUI_InitList(void)
{
	// init online list

	m_List_xxx.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	for (int i = 0; i < g_Column_Message_Count; i++)
	{
		m_List_xxx.InsertColumn(i, 
			g_Column_Message_Data[i].title, 
			LVCFMT_CENTER, 
			g_Column_Message_Data[i].nWidth);
		g_Column_Message_Width += g_Column_Message_Data[i].nWidth;       //得到总宽度
	}
	return 0;
}

void CMFCClistDlg::GUI_ShowMessage(bool bIsOK, CString strMsg)
{
	CString strIsOK, strTime;
	CTime t = CTime::GetCurrentTime();
	strTime = t.Format("%H:%M:%S");
	if (bIsOK)
	{
		strIsOK = "执行成功";
	}
	else {
		strIsOK = "执行失败";
	}
	m_List_xxx.InsertItem(0, strIsOK);
	m_List_xxx.SetItemText(0, 1, strTime);
	m_List_xxx.SetItemText(0, 2, strMsg);
}





void CMFCClistDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	// 命中目标
	double dcx = cx;     //对话框的总宽度
	if (m_List_xxx.m_hWnd != NULL)
	{
		CRect rc;
		rc.left = 1;             //列表的左坐标
		rc.top = 20;       //列表的上坐标
		rc.right = cx - 1;       //列表的右坐标
		rc.bottom = cy - 20;      //列表的下坐标
		m_List_xxx.MoveWindow(rc);
		for (auto i = 0; i < g_Column_Message_Count; i++) {  //遍历每一个列
			double dd = g_Column_Message_Data[i].nWidth;     //得到当前列的宽度
			dd /= g_Column_Message_Width;                    //看一看当前宽度占总长度的几分之几
			dd *= dcx;                                       //用原来的长度乘以所占的几分之几得到当前的宽度
			auto lenth = dd;                                 //转换为int 类型
			m_List_xxx.SetColumnWidth(i, (lenth));           //设置当前的宽度
		}

	}
}


void CMFCClistDlg::GUI_Dir_Delete()
{
	// TODO: 在此添加命令处理程序代码
	int i, iState;

	int nItemSelected = m_List_xxx.GetSelectedCount();        // 当前选择的条目
	int nItemCount = m_List_xxx.GetItemCount();               // 检索在列表视图控件中的项的数目。
	if (nItemSelected < 1)
		return;
	for (i = nItemCount - 1; i >= 0; i--)
	{
		iState = m_List_xxx.GetItemState(i, LVIS_SELECTED);   // 获取选择状态
		if (iState != 0)
		{

			m_List_xxx.DeleteItem(i);                         // 删除
		}
	}
}


void CMFCClistDlg::GUI_Dir_DeleteALL_Items()
{
	// TODO: 在此添加命令处理程序代码
	m_List_xxx.DeleteAllItems();
	m_List_xxx.SetRedraw(FALSE);
	//do erase and insert operation
	m_List_xxx.SetRedraw(TRUE);
	m_List_xxx.RedrawWindow();
}


void CMFCClistDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	CMenu	popup;
	popup.LoadMenu(IDR_MENU1);
	CMenu*	pM = popup.GetSubMenu(0);
	CPoint	p;
	GetCursorPos(&p);
	int	count = pM->GetMenuItemCount();
	if (m_List_xxx.GetSelectedCount() == 0)       //如果没有选中
	{
		for (int i = 2; i < count; i++)
		{
			pM->EnableMenuItem(i, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);          //菜单全部变灰
		}

	}
	pM->TrackPopupMenu(TPM_LEFTALIGN, p.x, p.y, this);
	*pResult = 0;
}


void CMFCClistDlg::GUI_Add_Check_Dir()
{
	// TODO: 在此添加命令处理程序代码
	CString m_strFileOut = _T("");
	TCHAR servPath[MAX_PATH];//用来存放文件夹路径  
	BROWSEINFO bi;
	LPITEMIDLIST pidl;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = servPath;
	bi.lpszTitle = _T("选择文件路径");
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	if ((pidl = SHBrowseForFolder(&bi)) != NULL)
	{
		if (SHGetPathFromIDList(pidl, servPath)) //得到文件夹的全路径，不要的话，只得本文件夹名  
		{

			GUI_ShowMessage(true, servPath);

		}
	}
	// 把变量内容更新到对话框
	UpdateData(FALSE);
}
