
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	//{
	//	TRACE0("δ�ܴ���������\n");
	//	return -1;      // δ�ܴ���
	//}

	//if (!m_wndStatusBar.Create(this))
	//{
	//	TRACE0("δ�ܴ���״̬��\n");
	//	return -1;      // δ�ܴ���
	//}
	//m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//// TODO: �������Ҫ��ͣ������������ɾ��������
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	Initialize();


	return 0;
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	m_UserClient.Broadcast();
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnClose()
{
	m_UserClient.Qiut();
	CFrameWnd::OnClose();
}

void CMainFrame::Initialize()
{
	if (m_UserServer.Init() != TRUE) {
		AfxMessageBox(_T("�û����������ʧ�ܣ�"));
	}
	if (m_UserClient.Init() != TRUE) {
		AfxMessageBox(_T("�û������ͻ���ʧ�ܣ�"));
	}

	m_UserClient.Broadcast();

	SetTimer(1, 1000 * 10, NULL);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cx = 802;
	cs.cy = 800;

	cs.style = cs.style & (~WS_THICKFRAME);
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~(WS_MAXIMIZEBOX); // �������
	cs.lpszClass = AfxRegisterWndClass(0);

	return TRUE;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void * pExtra, AFX_CMDHANDLERINFO * pHandlerInfo)
{
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext * pContext)
{
	// �зִ��ڣ� ���沿��ΪUserView, ���沿��ΪCFianlProjectView
	m_Splitter.CreateStatic(this, 2, 1);
	m_Splitter.CreateView(0, 0, RUNTIME_CLASS(UserView), CSize(1000, 300), pContext);
	m_Splitter.CreateView(1, 0, RUNTIME_CLASS(CFinalProjectView), CSize(1000, 400), pContext);

	// ��ȡUserView��ַ
	m_UserServer.m_pUserView = (UserView*)m_Splitter.GetPane(0, 0);

	// ��ȡChatView��ַ
	CFinalProjectView* pCFinalProjectView = (CFinalProjectView*)m_Splitter.GetPane(1, 0);

	m_UserServer.m_pFPView = pCFinalProjectView;

	pCFinalProjectView->m_pUserClient = &m_UserClient;

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

