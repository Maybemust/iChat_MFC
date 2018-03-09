
// FinalProjectView.cpp : CFinalProjectView ���ʵ��
//

#include "stdafx.h"
#include "FinalProject.h"

#include "FinalProjectView.h"
#include "MainFrm.h"
#include "FileThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFinalProjectView

IMPLEMENT_DYNCREATE(CFinalProjectView, CFormView)

BEGIN_MESSAGE_MAP(CFinalProjectView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CFinalProjectView::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_FILE, &CFinalProjectView::OnBnClickedButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CFinalProjectView::OnBnClickedButtonRefresh)
END_MESSAGE_MAP()

// CFinalProjectView ����/����

CFinalProjectView::CFinalProjectView()
	: CFormView(IDD_FINALPROJECT_FORM)
{
	// TODO: �ڴ˴���ӹ������
	m_pUserClient = NULL;

}

CFinalProjectView::~CFinalProjectView()
{
}

void CFinalProjectView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CHAT, m_wndChatList);
	DDX_Control(pDX, IDC_EDIT_CHAT, m_wndChatEdit);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_wndChatBtn);
}

void CFinalProjectView::AddChat(CString strChat, CString strIP)
{
	//AfxMessageBox(strChat);
	CString strData = strIP + _T(":") + strChat;
	int nItem = m_wndChatList.AddString(strData);
	m_wndChatList.SetCurSel(nItem);
}

BOOL CFinalProjectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CFinalProjectView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_wndFont.DeleteObject();
	m_wndFont.CreatePointFont(130, _T("΢���ź�"));
	m_wndChatEdit.SetFont(&m_wndFont);
}


// CFinalProjectView ���

#ifdef _DEBUG
void CFinalProjectView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFinalProjectView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

#endif //_DEBUG


// CFinalProjectView ��Ϣ�������


void CFinalProjectView::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pUserClient == NULL)
	{
		return;
	}
	CString strData = _T("");
	m_wndChatEdit.GetWindowText(strData);

	// ���
	m_wndChatEdit.SetSel(0, -1);
	m_wndChatEdit.Clear();

	// ���͵���Ϣ����Ϊ��
	if (strData.IsEmpty())
	{
		AfxMessageBox(_T("���͵���Ϣ����Ϊ�գ�"));
		return;
	}

	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CUserView* pUserView = (CUserView*)pMain->m_Splitter.GetPane(0, 0);

	CListCtrl& ctrl = pUserView->GetListCtrl();
	int nCount = ctrl.GetItemCount();

	bool flag = false;
	for (size_t i = 0; i < nCount; i++)
	{
		if (ctrl.GetCheck(i))
		{
			flag = true;
			//AfxMessageBox(strData);
			CString strIP = ctrl.GetItemText(i, 2);
			//AfxMessageBox(strIP);
			m_pUserClient->SendChat(strData, strIP);
		}
	}

	if (flag == true)
	{
		AddChat(strData, _T("My word"));
	}
	else
	{
		AfxMessageBox(_T("��ѡ���͵Ķ���"));
	}
}


void CFinalProjectView::OnBnClickedButtonFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() != IDOK)
	{
		AfxMessageBox(_T("��ѡ���ļ�"));
		return;
	}
	CString strFilePath = dlg.GetPathName();

	// ��ȡ�û���ͼ
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CUserView* pUserView = (CUserView*)pMain->m_Splitter.GetPane(0, 0);

	CListCtrl& ctrl = pUserView->GetListCtrl();
	int nCount = ctrl.GetItemCount();

	for (size_t i = 0; i < nCount; i++)
	{
		if (ctrl.GetCheck(i))
		{
			CString strIP = ctrl.GetItemText(i, 2);

			// ���������߳�
			CFileThread* pFileThread = (CFileThread*)AfxBeginThread(RUNTIME_CLASS(CFileThread,
				THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED));

			// ���ò���
			pFileThread->SetSocket(strFilePath, strIP, TRUE);

			// ��ʼ�߳�
			pFileThread->ResumeThread();
		}
	}
}


void CFinalProjectView::OnBnClickedButtonRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CUserView* pUserView = (CUserView*)pMain->m_Splitter.GetPane(0, 0);

	CListCtrl& ctrl = pUserView->GetListCtrl();
	int nCount = ctrl.GetItemCount();
	for (size_t i = 0; i < nCount; i++)
	{
		ctrl.DeleteItem(i);
	}
	pMain->m_UserClient.Broadcast();

}
