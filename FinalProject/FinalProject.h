
// FinalProject.h : FinalProject Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CFinalProjectApp:
// �йش����ʵ�֣������ FinalProject.cpp
//

class CFinalProjectApp : public CWinApp
{
public:
	CFinalProjectApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFinalProjectApp theApp;
