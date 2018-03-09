// FileSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FileSend.h"
#include "afxdialogex.h"


// FileSend �Ի���

IMPLEMENT_DYNAMIC(FileSend, CDialog)

FileSend::FileSend(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_SEND, pParent)
{
	m_bSend = FALSE;
}

FileSend::~FileSend()
{
}

void FileSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SEND, m_Info);
	DDX_Control(pDX, IDC_PROGRESS_SEND, m_wndSendProgress);
}

BOOL FileSend::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_bSend = FALSE;
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	Send();
	return TRUE;
}


BEGIN_MESSAGE_MAP(FileSend, CDialog)
	ON_BN_CLICKED(IDOK, &FileSend::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &FileSend::OnBnClickedCancel)
END_MESSAGE_MAP()


// FileSend ��Ϣ�������


void FileSend::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


void FileSend::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}

UINT FileSend::SendThread(LPVOID pParam)
{
	FileSend* pThis = (FileSend*)pParam;
	pThis->m_FileCilent.SendFile(pThis->m_strFilename, 
		&pThis->m_wndSendProgress);
	pThis->m_Info.SetWindowText(_T("�ļ��������"));
	return 0;
}

void FileSend::Send()
{
	if (m_bSend == FALSE)
	{
		if (m_FileCilent.Init() == FALSE)
		{
			AfxMessageBox(_T("��ʼ���ļ��ͻ���ʧ��"));
			return;
		}
		if (m_FileCilent.ConnectServer(m_strDesIP))
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
