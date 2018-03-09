#pragma once
#include "stdafx.h"


// UserView ��ͼ

class UserView : public CListView
{
	DECLARE_DYNCREATE(UserView)

protected:
	UserView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~UserView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

// ����
public:
	// ����û�
	void AddUser(CString strName, CString strIP);
	// �����û�
	int FindUser(CString strIP);
	// ɾ���û�
	void DeleteUser(CString strIP);

// override
protected:
	virtual void onDraw(CDC* pDC);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	
protected:
	// ����ѡ����Ŀ
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// �жϸ��̵߳�heartbeat
	afx_msg void OnTimer(UINT nIDEVENT);
};


