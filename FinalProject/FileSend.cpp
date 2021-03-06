// FileSend.cpp : 实现文件
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FileSend.h"
#include "afxdialogex.h"


// FileSend 对话框

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


// FileSend 消息处理程序


void CFileSendDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CFileSendDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

UINT CFileSendDlg::SendThread(LPVOID pParam)
{
	CFileSendDlg* pThis = (CFileSendDlg*)pParam;
	pThis->m_FileCilent.SendFile(pThis->m_strFilename, 
		&pThis->m_wndSendProgress);
	pThis->m_Info.SetWindowText(_T("文件发送完毕"));
	return 0;
}

void CFileSendDlg::Send()
{
	if (m_bSend == FALSE)
	{
		if (m_FileCilent.Init() == FALSE)
		{
			AfxMessageBox(_T("初始化文件客户端失败"));
			return;
		}
		if (m_FileCilent.ConnectServer(m_strDesIP) == FALSE)
		{
			AfxMessageBox(_T("连接服务器失败"));
			return;
		}
		m_Info.SetWindowText(_T("正在发送文件……"));
		// 启动发送线程
		AfxBeginThread(SendThread, this);
		m_bSend = TRUE;
	}
	else
	{
		AfxMessageBox(_T("请等待当前文件发送完毕"));
		return;
	}
}
