
// ģ��Gh0st�������ߵ�ַDlg.h : ͷ�ļ�
//

#pragma once


// Cģ��Gh0st�������ߵ�ַDlg �Ի���
class Cģ��Gh0st�������ߵ�ַDlg : public CDialogEx
{
// ����
public:
	Cģ��Gh0st�������ߵ�ַDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GH0ST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_remote_host;
	CString m_remote_port;

	CString m_encode;
	afx_msg void OnBnBuild();
	char * MyEncode(char *str); //���ܺ���
	int base64_encode(const void *data, int size, char **str); //base64_encode
	int pos(char c);
	int base64_decode(const char *str, char **data);
	char* MyDecode(char *str);
	afx_msg void OnBnGetLoginInfo();
	CString m_decode;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
