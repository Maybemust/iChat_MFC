// FileThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FileThread.h"


// CFileThread

IMPLEMENT_DYNCREATE(CFileThread, CWinThread)

CFileThread::CFileThread()
{
}

CFileThread::~CFileThread()
{
}

BOOL CFileThread::InitInstance()
{
	// TODO:    �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CFileThread::ExitInstance()
{
	// TODO:    �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CFileThread, CWinThread)
END_MESSAGE_MAP()


// CFileThread ��Ϣ�������
