#pragma once
#include "FileClient.h"


// FileSend �Ի���

class FileSend : public CDialog
{
	DECLARE_DYNAMIC(FileSend)

public:
	FileSend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FileSend();

private:
	CStatic		   m_Info;				// ������Ϣ
	CProgressCtrl  m_wndSendProgress;	// ���ͽ�����
	FileClient     m_FileCilent;		// �ļ��ͻ���
	BOOL		   m_bSend;			// �շ���־

public:
	CString	       m_strDesIP;			// Ŀ��IP
	CString        m_strFilename;		// ������ļ�


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	static UINT SendThread(LPVOID pParam);
	void Send();
};
