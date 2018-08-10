
// ģ��Gh0st�������ߵ�ַDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ģ��Gh0st�������ߵ�ַ.h"
#include "ģ��Gh0st�������ߵ�ַDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cģ��Gh0st�������ߵ�ַDlg �Ի���



Cģ��Gh0st�������ߵ�ַDlg::Cģ��Gh0st�������ߵ�ַDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GH0ST_DIALOG, pParent)
	, m_remote_host(_T(""))
	, m_remote_port(_T(""))
	, m_encode(_T(""))
	, m_decode(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cģ��Gh0st�������ߵ�ַDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_remote_host);
	DDX_Text(pDX, IDC_EDIT3, m_remote_port);
	DDX_Text(pDX, IDC_EDIT7, m_encode);
	DDX_Text(pDX, IDC_EDIT8, m_decode);
}

BEGIN_MESSAGE_MAP(Cģ��Gh0st�������ߵ�ַDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cģ��Gh0st�������ߵ�ַDlg::OnBnBuild)
	ON_BN_CLICKED(IDC_BUTTON2, &Cģ��Gh0st�������ߵ�ַDlg::OnBnGetLoginInfo)
END_MESSAGE_MAP()


// Cģ��Gh0st�������ߵ�ַDlg ��Ϣ�������

BOOL Cģ��Gh0st�������ߵ�ַDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cģ��Gh0st�������ߵ�ַDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cģ��Gh0st�������ߵ�ַDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cģ��Gh0st�������ߵ�ַDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Cģ��Gh0st�������ߵ�ַDlg::OnBnBuild()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_remote_host.Replace(L" ", L"");
	m_remote_port.Replace(L" ", L"");

	CString str = m_remote_host + ":" + m_remote_port;
	str.MakeLower();
	TCHAR * pWStrKey;         // �ϲ��������

	// ��������
	pWStrKey = new TCHAR[str.GetLength() + 1];
	pWStrKey = str.GetBuffer(0);

	// ��һ�ε���ȷ��ת�����ֽ��ַ����ĳ��ȣ����ڿ��ٿռ�
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWStrKey, wcslen(pWStrKey), NULL, 0, NULL, NULL);
	// ���ַ�
	char* pCStrKey = new char[pSize + 1];
	// �ڶ��ε��ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
	WideCharToMultiByte(CP_OEMCP, 0, pWStrKey, wcslen(pWStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';

	// ����char*
	m_encode = MyEncode(pCStrKey);

	m_encode.Insert(0, L"AAAA");
	m_encode += "AAAA";

	UpdateData(FALSE);
}

void Cģ��Gh0st�������ߵ�ַDlg::OnBnGetLoginInfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);


	// 1 ��ȡ���ܱ༭�ؼ�����ַ���
	int pSize = m_encode.GetLength() + 1;
	wchar_t	* pStart, *pEnd;
	wchar_t strKey[] = L"AAAA";
	wchar_t strEncode[1024];

	// �õ��ʼ���ַ���,���ǰ����AAAA�͸�ֵ��pStart
	pStart = wcsstr(m_encode.GetBuffer(0), strKey);
	// ǰ�ƶ�4���ֽڣ�Ҳ��������AAAA
	pStart += 4;
	// ���AAAAƥ�䲻����strKey��Ҳ����AAAA��ֵ��pEnd
	pEnd = wcsstr(pStart, strKey);
	// ���ԭ��AAAA�ַ���
	wmemset(strEncode, 0, wcslen(pStart) + 1);
	// ȡkeyֵ֮������ݣ������ַ��� - �ַ������ȣ�ȡǰ�����ʵ�����ַ���
	wmemcpy(strEncode, pStart, pEnd - pStart);
	// ���ַ�
	char* pCStrKey = new char[wcslen(strEncode) + 1];
	// ���ý�˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
	WideCharToMultiByte(CP_OEMCP, 0, strEncode, wcslen(strEncode) + 1, pCStrKey, wcslen(strEncode) + 1, NULL, NULL);
	pCStrKey[pSize] = '\0';

	// ���ܴ���
	m_decode = MyDecode(pCStrKey);


	UpdateData(FALSE);
}

// Base64����
static char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int Cģ��Gh0st�������ߵ�ַDlg::base64_encode(const void *data, int size, char **str)
{
	char *s, *p;
	int i;
	int c;
	const unsigned char *q;

	p = s = (char*)malloc(size * 4 / 3 + 4);
	if (p == NULL)
		return -1;
	q = (const unsigned char*)data;
	i = 0;
	for (i = 0; i < size;) {
		c = q[i++];
		c *= 256;
		if (i < size)
			c += q[i];
		i++;
		c *= 256;
		if (i < size)
			c += q[i];
		i++;
		p[0] = base64[(c & 0x00fc0000) >> 18];  //base64
		p[1] = base64[(c & 0x0003f000) >> 12];
		p[2] = base64[(c & 0x00000fc0) >> 6];
		p[3] = base64[(c & 0x0000003f) >> 0];
		if (i > size)
			p[3] = '=';
		if (i > size + 1)
			p[2] = '=';
		p += 4;
	}
	*p = 0;
	*str = s;
	return strlen(s);
}

// ���ܱ���
char * Cģ��Gh0st�������ߵ�ַDlg::MyEncode(char *str)
{
	int		i, len;
	char	*s, *data;
	// �ַ�������
	len = strlen(str) + 1;
	// �����ַ������Ӧ���ڴ�ռ�
	s = (char *)malloc(len);
	// ���ַ������������ٳ�����ָ����
	memcpy(s, str, len);
	// ������
	for (i = 0; i < len; i++)
	{
		s[i] ^= 0x19;
		s[i] += 0x86;
	}
	// Base64����
	base64_encode(s, len, &data);
	free(s);

	return data;
}

// ������Կ
int Cģ��Gh0st�������ߵ�ַDlg::pos(char c)
{
	char *p;
	for (p = base64; *p; p++)
		if (*p == c)
			return p - base64;
	return -1;
}

// Base64����
int Cģ��Gh0st�������ߵ�ַDlg::base64_decode(const char *str, char **data)
{
	const char *s, *p;
	unsigned char *q;
	int c;
	int x;
	int done = 0;
	int len;
	s = (const char *)malloc(strlen(str));
	q = (unsigned char *)s;
	for (p = str; *p && !done; p += 4) {
		x = pos(p[0]);
		if (x >= 0)
			c = x;
		else {
			done = 3;
			break;
		}
		c *= 64;

		x = pos(p[1]);
		if (x >= 0)
			c += x;
		else
			return -1;
		c *= 64;

		if (p[2] == '=')
			done++;
		else {
			x = pos(p[2]);
			if (x >= 0)
				c += x;
			else
				return -1;
		}
		c *= 64;

		if (p[3] == '=')
			done++;
		else {
			if (done)
				return -1;
			x = pos(p[3]);
			if (x >= 0)
				c += x;
			else
				return -1;
		}
		if (done < 3)
			*q++ = (c & 0x00ff0000) >> 16;

		if (done < 2)
			*q++ = (c & 0x0000ff00) >> 8;
		if (done < 1)
			*q++ = (c & 0x000000ff) >> 0;
	}

	len = q - (unsigned char*)(s);

	*data = (char*)realloc((void *)s, len);

	return len;
}

// ���ܺ���
char* Cģ��Gh0st�������ߵ�ַDlg::MyDecode(char *str)
{
	int		i, len;
	char	*data = NULL;
	len = base64_decode(str, &data);

	for (i = 0; i < len; i++)
	{
		data[i] -= 0x86;
		data[i] ^= 0x19;

		//data[i] -= 0x6;
		//data[i] ^= 0x12;
	}
	return data;
}



BOOL Cģ��Gh0st�������ߵ�ַDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_BUTTON1)//���»س��������ǰ���������Լ������Ŀؼ���
		{
			// ���������£�������»س�ʱ����������Ҫ�Ŀؼ���
			OnBnBuild();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
