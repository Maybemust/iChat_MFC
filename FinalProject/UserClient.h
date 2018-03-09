#pragma once
#include "stdafx.h"
#include "UserView.h"

class CUserClient
{
public:
	CUserClient();
	~CUserClient();

public:
	// ��ʼ���ͻ���
	BOOL Init();
	// �㲥����
	BOOL Broadcast();
	// ��������
	BOOL SendData(CHAR* psxData, UINT nlength, LPCSTR lpDesIP = NULL);
	// �����ر��˳�����
	BOOL Qiut();
	// ������Ϣ
	BOOL SendChat(CString strData, CString strDesIP);

public:
	SOCKET m_ClientSocket;  // �ͻ���Socket
};

