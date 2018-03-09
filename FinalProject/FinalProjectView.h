
// FinalProjectView.h : CFinalProjectView ��Ľӿ�
//

#pragma once
#include "stdafx.h"
#include "UserClient.h"
#include "Resource.h"


class CFinalProjectView : public CFormView
{
protected: // �������л�����
	CFinalProjectView();
	DECLARE_DYNCREATE(CFinalProjectView)

public:
	enum{ IDD = IDD_FINALPROJECT_FORM };

	CListBox m_wndChatList;
	CEdit	 m_wndChatEdit;
	CButton  m_wndChatBtn;
	CFont    m_wndFont;

// ����
public:
	CUserClient* m_pUserClient;

// ����
public:
	void AddChat(CString strChat, CString strIP);

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CFinalProjectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonFile();
	afx_msg void OnBnClickedButtonRefresh();
};

