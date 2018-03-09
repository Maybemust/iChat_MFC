// FileSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FileSend.h"
#include "afxdialogex.h"


// FileSend �Ի���

IMPLEMENT_DYNAMIC(CFileSendDlg, CDialog)

CFileSendDlg::CFileSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_SEND, pParent)
{
	m_bSend = FALSE;
}

CFileSendDlg::~CFileSendDlg()
{
}

void CFileSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SEND, m_Info);
	DDX_Control(pDX, IDC_PROGRESS_SEND, m_wndSendProgress);
}

BOOL CFileSendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_bSend = FALSE;
	//GetDlgItem(IDOK)->EnableWindow(FALSE);
	Send();
	return TRUE;
}


BEGIN_MESSAGE_MAP(CFileSendDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CFileSendDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CFileSendDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// FileSend ��Ϣ�������


void CFileSendDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void CFileSendDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}

UINT CFileSendDlg::SendThread(LPVOID pParam)
{
	CFileSendDlg* pThis = (CFileSendDlg*)pParam;
	pThis->m_FileCilent.SendFile(pThis->m_strFilename, 
		&pThis->m_wndSendProgress);
	pThis->m_Info.SetWindowText(_T("�ļ��������"));
	return 0;
}

void CFileSendDlg::Send()
{
	if (m_bSend == FALSE)
	{
		if (m_FileCilent.Init() == FALSE)
		{
			AfxMessageBox(_T("��ʼ���ļ��ͻ���ʧ��"));
			return;
		}
		if (m_FileCilent.ConnectServer(m_strDesIP) == FALSE)
		{
			AfxMessageBox(_T("���ӷ�����ʧ��"));
			return;
		}
		m_Info.SetWindowText(_T("���ڷ����ļ�����"));
		// ���������߳�
		AfxBeginThread(SendThread, this);
		m_bSend = TRUE;
	}
	else
	{
		AfxMessageBox(_T("��ȴ���ǰ�ļ��������"));
		return;
	}
}
