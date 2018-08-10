
// ģ��Gh0st�������ߵ�ַ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cģ��Gh0st�������ߵ�ַApp: 
// �йش����ʵ�֣������ ģ��Gh0st�������ߵ�ַ.cpp
//

class Cģ��Gh0st�������ߵ�ַApp : public CWinApp
{
public:
	Cģ��Gh0st�������ߵ�ַApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cģ��Gh0st�������ߵ�ַApp theApp;