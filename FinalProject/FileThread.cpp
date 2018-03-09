// FileThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FileThread.h"


// CFileThread

IMPLEMENT_DYNCREATE(CFileThread, CWinThread)

CFileThread::CFileThread()
{
	m_bSendDlg = FALSE;
}

CFileThread::~CFileThread()
{
}

BOOL CFileThread::InitInstance()
{
	// TODO:    �ڴ�ִ���������̳߳�ʼ��
	if (m_bSendDlg == FALSE)
	{
		m_pMainWnd = &m_FileReceiveDlg;
		m_FileReceiveDlg.DoModal();
	}
	else
	{
		m_pMainWnd = &m_FileSendDlg;
		m_FileSendDlg.DoModal();
	}
	
	return TRUE;
}

int CFileThread::ExitInstance()
{
	// TODO:    �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

// �����ļ�
void CFileThread::SetSocket(SOCKET socket, CString strIP, BOOL bFileSendDlg)
{
	m_FileReceiveDlg.m_ClientSocket = socket;
	m_FileReceiveDlg.m_strIP = strIP;
	m_bSendDlg = bFileSendDlg;
}

// �����ļ�
void CFileThread::SetSocket(CString strFilename, CString strIP, BOOL bFileSendDlg)
{
	m_FileSendDlg.m_strFilename = strFilename;
	m_FileSendDlg.m_strDesIP = strIP;
	m_bSendDlg = bFileSendDlg;
}

BEGIN_MESSAGE_MAP(CFileThread, CWinThread)
END_MESSAGE_MAP()


// CFileThread ��Ϣ�������
