// UserView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FinalProject.h"
#include "UserView.h"

// UserView

IMPLEMENT_DYNCREATE(UserView, CListView)

UserView::UserView()
{

}

UserView::~UserView()
{
}

BEGIN_MESSAGE_MAP(UserView, CListView)
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// UserView ���

#ifdef _DEBUG
void UserView::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void UserView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif
#endif //_DEBUG


// UserView ��Ϣ�������
// ����û����û���Ϣ�б�
void UserView::AddUser(CString strName, CString strIP)
{
	CListCtrl& ctrl = GetListCtrl();
	// ��ȡ��ǰ�б�����
	int nItem = ctrl.GetItemCount();
	// ����б��д��ڵ�ǰ�û�������heartbeat��Ϊ1����ʾ����
	if (FindUser(strIP) != -1)
	{
		ctrl.SetItemData(nItem, 1);
		return;
	}
	//AfxMessageBox(strName);
	nItem = ctrl.InsertItem(nItem, NULL);
	ctrl.SetItemText(nItem, 1, strName);
	ctrl.SetItemText(nItem, 2, strIP);
	// �¼��û���heartbeat��Ϊ1����ʾ����
	ctrl.SetItemData(nItem, 1);
	return;
}

// ���û���Ϣ�б��в�ѯ�û�
int UserView::FindUser(CString strIP)
{
	CListCtrl &ctrl = GetListCtrl();
	int nCount = ctrl.GetItemCount();

	for (size_t i = 0; i < nCount; i++)
	{
		// ��ȡIP��ַ
		CString strItemIP = ctrl.GetItemText(i, 2);
		// ������ҵ����û�
		if (strItemIP.CompareNoCase(strIP) == 0)
		{
			return i;
		}
	}

	// δ�鵽���û�
	return -1;
}

// ɾ���û��������û�������ʱ
void UserView::DeleteUser(CString strIP)
{
	// �����û�
	int nItem = FindUser(strIP);
	if (nItem == -1)
	{
		AfxMessageBox(strIP + "is not Found");
		return;
	}
	// ɾ���û�
	CListCtrl& ctrl = GetListCtrl();
	ctrl.DeleteItem(nItem);
	return;
}

void UserView::onDraw(CDC * pDC)
{
	CDocument* pDoc = GetDocument();
	return;
}

// ��ֹ�϶���ͷ
BOOL UserView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT * pResult)
{
	// ����������Ϣ֪ͨ��
	NMHEADER* pNMheader = (NMHEADER*)lParam;

	if ((pNMheader->hdr.code == HDN_BEGINTRACKW) |
		(pNMheader->hdr.code == HDN_DIVIDERDBLCLICKW))
	{
		*pResult = TRUE;
		return TRUE;
	}

	return CWnd::OnNotify(wParam, lParam, pResult);
}

// ��������
int UserView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	// ������ʽ
	ModifyStyle(0, LVS_REPORT);

	CListCtrl& ctrl = GetListCtrl();
	ctrl.SetExtendedStyle(LVS_EX_CHECKBOXES);
	ctrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 40);
	ctrl.InsertColumn(1, _T("���������"), LVCFMT_LEFT, 300);
	ctrl.InsertColumn(2, _T("IP��ַ"), LVCFMT_LEFT, 300);

	SetTimer(2, 10000, NULL);
	return 0;
}

// ����heartbeat
void UserView::OnTimer(UINT nIDEVENT)
{
	if (nIDEVENT != 2)
	{
		return;
	}

	CListCtrl& ctrl = GetListCtrl();
	int nCount = ctrl.GetItemCount();

	for (size_t i = 0; i < nCount; i++)
	{
		DWORD dwData = ctrl.GetItemData(i);
		if (dwData > 0)
		{// ���heartbeatֵΪ1������Ϊ0
			ctrl.SetItemData(i, 0);
		}
		else
		{// ���heartbeatֵΪ0����ɾ��
			ctrl.DeleteItem(i);
		}
	}
	CListView::OnTimer(nIDEVENT);
	return;
}
