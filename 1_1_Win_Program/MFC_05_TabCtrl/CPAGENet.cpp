// CPAGENet.cpp: 实现文件
//

#include "stdafx.h"
#include "MFC_05_TabCtrl.h"
#include "CPAGENet.h"
#include "afxdialogex.h"


// CPAGENet 对话框

IMPLEMENT_DYNAMIC(CPAGENet, CDialogEx)

CPAGENet::CPAGENet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE_NETWORK, pParent)
{

}

CPAGENet::~CPAGENet()
{
}

void CPAGENet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPAGENet, CDialogEx)
END_MESSAGE_MAP()


// CPAGENet 消息处理程序
