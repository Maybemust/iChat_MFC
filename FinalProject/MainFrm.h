
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "UserClient.h"
#include "UserServer.h"
#include "FileServer.h"

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	CMainFrame();
	// �ָ�������
	CSplitterWnd m_Splitter;
	// �ͻ���
	CUserClient m_UserClient;
	// �����
	CUserServer m_UserServer;
	// �ļ�������
	CFileServer m_FileServer;

// ����
public:
	void Initialize();

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

};


