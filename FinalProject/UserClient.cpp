#include "stdafx.h"
#include "UserClient.h"

#include <winsock2.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "WS2_32.lib")


UserClient::UserClient()
{
	m_ClientSocket = INVALID_SOCKET;
}


UserClient::~UserClient()
{
	if (m_ClientSocket != INVALID_SOCKET)
	{
		::closesocket(m_ClientSocket);
		::WSACleanup();
	}
}

// ��ʼ���ͻ���
BOOL UserClient::Init()
{
	// ��ʼ��WS2_32.dll
	WSADATA wsData;
	WORD socketVersion = MAKEWORD(2, 0);
	::WSAStartup(socketVersion, &wsData);
	
	// ����SOCKET
	m_ClientSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_ClientSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Failed socket()"));
		return FALSE;
	}

	// ���ù㲥ģʽ
	BOOL bBroadcast = TRUE;
	setsockopt(m_ClientSocket, SOL_SOCKET, SO_BROADCAST, 
		(char FAR*)&bBroadcast, sizeof(bool));

	return TRUE;
}

// �㲥����
BOOL UserClient::Broadcast()
{
	// ��������
	USERBROADCAST user = { 0 };
	user.header.dwVersion = 1;
	user.header.dwCmdID = NETCMDID_USERBROADCAST;
	user.header.dwDataLength = sizeof(user) - sizeof(NETHEADER);
	DWORD nLength = 128;

	GetComputerName(user.szName, &nLength);

	SendData((CHAR*)&user, sizeof(user));
	return TRUE;
}

BOOL UserClient::SendData(CHAR * psxData, UINT nlength, LPCSTR lpDesIP)
{
	//AfxMessageBox((LPCTSTR)lpDesIP);
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_USERSERVICE);

	if (lpDesIP == NULL)
	{
		// ���͹㲥����
		addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
	}
	else
	{
		addr.sin_addr.S_un.S_addr = inet_addr(lpDesIP);
	}

	BOOL bSend = sendto(m_ClientSocket, psxData, nlength, 0, (struct sockaddr*)&addr, sizeof(addr));
	if (bSend == SOCKET_ERROR)
	{
		AfxMessageBox(_T("Failed sendto()"));
		return FALSE;
	}
	return TRUE;
}

// �û������˳�
BOOL UserClient::Qiut()
{
	// ��������
	USERQUIT quit;
	quit.header.dwVersion = 1;
	quit.header.dwCmdID = NETCMDID_USERQUIT;
	quit.header.dwDataLength = sizeof(quit) - sizeof(USERQUIT);
	quit.dwExitCode = 0;
	
	SendData((CHAR*)&quit, sizeof(quit));
	return TRUE;
}

// 
BOOL UserClient::SendChat(CString strData, CString strDesIP)
{
	// ��������
	USERCHAT chat;
	chat.header.dwVersion = 1;
	chat.header.dwCmdID = NETCMDID_USERCHAT;
	chat.header.dwDataLength = sizeof(chat) - sizeof(USERCHAT);

	strcpy(chat.szChat, strData);
	
	return SendData((CHAR*)&chat, sizeof(chat), strDesIP);
}
