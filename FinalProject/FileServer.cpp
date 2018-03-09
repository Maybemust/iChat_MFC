#include "stdafx.h"
#include "FileServer.h"
#include "FileThread.h"
#include <winsock2.h>

#pragma comment(lib,"WS2_32.lib")

CFileServer::CFileServer()
{
}


CFileServer::~CFileServer()
{
}

BOOL CFileServer::Init()
{
	// ��ʼ��WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	// ����socket
	m_ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ServerSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Failed socket() for File Server"));
		return FALSE;
	}

	// ��IP�˿�
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_FILESERVICE);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	// ��
	bind(m_ServerSocket, (struct sockaddr*)&addr, sizeof(addr));
	// ����
	listen(m_ServerSocket, 5);
	// �����Ⱥ�ͻ��˵��߳�
	AfxBeginThread(FileThread, this);

	return TRUE;
}

UINT CFileServer::FileThread(LPVOID pParam)
{
	CFileServer* pThis = (CFileServer*)pParam;

	while (true)
	{
		// ����
		struct sockaddr_in sin;
		int nLength = sizeof(sin);
		SOCKET ClientSocket = accept(pThis->m_ServerSocket,
			(SOCKADDR*)&sin, &nLength);

		if (ClientSocket == INVALID_SOCKET)
		{
			// TODO

		}

		LPSTR pszIP = inet_ntoa(sin.sin_addr);
		pThis->OnConnect(ClientSocket, pszIP);
	}	
	return 0;
}

void CFileServer::OnConnect(SOCKET ClientSocket, LPSTR pszIP)
{
	// ���������߳�
	CFileThread* pFileThread = (CFileThread*)AfxBeginThread(RUNTIME_CLASS(CFileThread,
		THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED));

	// ���ò���
	pFileThread->SetSocket(ClientSocket, pszIP);

	// ��ʼ�߳�
	pFileThread->ResumeThread();
}
