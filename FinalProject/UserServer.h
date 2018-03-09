#pragma once

#include "UserView.h"
#include "stdafx.h"
#include "FinalProjectView.h"

class UserServer
{
public:
	UserServer();
	~UserServer();

public:
	// ��ʼ��User������
	BOOL Init();
	// �������ݵ��߳�
	static UINT UserThread(LPVOID pParam);
	// �����û��㲥����������
	BOOL OnUserBroadcast(LPUSERBROADCAST pUserBroadcast, LPCSTR lpSrcIP);
	// ������������
	BOOL OnUserChat(LPUSERCHAT pUserChat, LPCSTR lpSrcIP);
	// �û��˳�
	BOOL OnUserQuit(LPUSERQUIT pUserQuit, LPCSTR lpSrcIP);
public:
	SOCKET	                m_ServerSocket; // ������Socket
	UserView*	            m_pUserView;    // �û��б�
	CFinalProjectView*		m_pFPView;
};

