// FileReceive.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FileReceive.h"
#include "afxdialogex.h"


// FileReceive �Ի���

IMPLEMENT_DYNAMIC(CFileReceiveDlg, CDialog)

CFileReceiveDlg::CFileReceiveDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_RECEIVE, pParent)
{
	m_ClientSocket = INVALID_SOCKET;
}

CFileReceiveDlg::~CFileReceiveDlg()
{
	if (m_ClientSocket != INVALID_SOCKET)
	{
		::closesocket(m_ClientSocket);
	}
}

void CFileReceiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_RECEIVE, m_Info);
	DDX_Control(pDX, IDC_PROGRESS_RECEIVE, m_wndProgress);
}

BOOL CFileReceiveDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	NETHEADER header;
	Receive((LPSTR)&header, sizeof(header));
	Receive((LPSTR)&m_SendFile, sizeof(m_SendFile));

	SetWindowText(m_strIP);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CFileReceiveDlg, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CFileReceiveDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CFileReceiveDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// FileReceive ��Ϣ�������


// �����߳�
UINT CFileReceiveDlg::ReceiveThread(LPVOID pParam)
{
	CFileReceiveDlg* pThis = (CFileReceiveDlg*)pParam;
	// ��ȡ�ļ���С
	DWORD nLength = pThis->m_SendFile.dwFileLength;

	// �����ļ�
	CFile file;
	if (file.Open(pThis->m_strFilePath, 
		CFile::modeCreate | CFile::modeWrite) == FALSE)
	{
		AfxMessageBox(_T("�޷�д���ļ�������Ȩ��"));
		return 0;
	}
	
	// ���ý�����
	pThis->m_wndProgress.SetRange32(0, nLength);
	pThis->m_Info.SetWindowText(_T("���ڽ������ݡ���"));

	// ��������
	CHAR szBuffer[4096];
	DWORD nRemain = nLength;
	while (nRemain > 0)
	{
		// ������յ�������
		DWORD nReceive = 4096 < nRemain ? 4096 : nRemain;

		// ��������
		pThis->Receive(szBuffer, nReceive);
		// д���ļ�
		file.Write(szBuffer, nReceive);
		// ����ʣ������
		nRemain -= nReceive;

		// ���ý�����
		pThis->m_wndProgress.SetPos(nLength - nRemain);
	}
	pThis->m_Info.SetWindowText(_T("�������ݳɹ�"));
	// �ر��ļ�
	file.Close();

	return 0;
}

BOOL CFileReceiveDlg::Receive(LPVOID pData, DWORD nLength)
{
	LPSTR pTemp = (LPSTR)pData;
	int nRemain = nLength;
	while (nRemain > 0)
	{
		int nReceive = recv(m_ClientSocket, pTemp, nRemain, 0);
		if (nReceive == SOCKET_ERROR)
		{
			AfxMessageBox(_T("Failed to recv()"));
			return FALSE;
		}
		nRemain -= nReceive;
		pTemp += nReceive;
	}
	
	return TRUE;
}

void CFileReceiveDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CFileReceiveDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(FALSE, NULL, m_SendFile.szFileName);
	if (dlg.DoModal() != IDOK)
	{
		AfxMessageBox(_T("��ѡ���ļ�����·��"));
		return;
	}

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	// �õ�·������
	m_strFilePath = dlg.GetPathName();

	AfxBeginThread(ReceiveThread, this);

	// CDialog::OnOK();
}
