#pragma once
#include "FileReceive.h"
#include "FileSend.h"


// CFileThread

class CFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CFileThread)

protected:
	CFileThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFileThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CFileReceiveDlg		m_FileReceiveDlg;
	CFileSendDlg		m_FileSendDlg;

public:
	BOOL m_bSendDlg;
	// �����ļ�
	void SetSocket(SOCKET socket, CString strIP, BOOL bFileSendDlg = FALSE);
	// �����ļ�
	void SetSocket(CString strFilename, CString strIP, BOOL bFileSendDlg = TRUE);
};


