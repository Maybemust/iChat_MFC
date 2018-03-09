#include "stdafx.h"
#include "FileClient.h"


FileClient::FileClient()
{
	m_ClientSocket = INVALID_SOCKET;
}


FileClient::~FileClient()
{
	if (m_ClientSocket != INVALID_SOCKET)
	{
		::closesocket(m_ClientSocket);
		::WSACleanup();
	}
}

BOOL FileClient::Init()
{
	// ����socket
	m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
	if (m_ClientSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("��ʼ���ļ��ͻ��˷��ʹ���"));
		return FALSE;
	}
	return TRUE;
}

BOOL FileClient::ConnectServer(LPCSTR lpServerIP)
{
	// ���ӷ�����
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_FILESERVICE);
	addr.sin_addr.S_un.S_addr = inet_addr(lpServerIP);
	if (connect(m_ClientSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("File to connect"));
		return FALSE;
	}

	return TRUE;
}

BOOL FileClient::SendFile(LPCSTR pszFilePath, CProgressCtrl * pWndProgress)
{
	// ��������ͷ
	NETHEADER header;
	header.dwVersion = 1;
	header.dwCmdID = NETCMDID_SENDFILE;
	header.dwDataLength = sizeof(SENDFILE);
	SendData(&header, sizeof(header));

	// �����ļ���Ϣ
	CFile file;
	if (file.Open(pszFilePath, CFile::modeRead) == FALSE)
	{
		AfxMessageBox(_T("Failed to open file"));
		return FALSE;
	}

	SENDFILE sendFile;
	strcpy(sendFile.szFileName, file.GetFileName);
	sendFile.dwFileLength = file.GetLength();
	SendData(&sendFile, sizeof(sendFile));

	if (pWndProgress != NULL)
	{
		pWndProgress->SetRange32(0, sendFile.dwFileLength);
	}
	// �����ļ�����
	CHAR szBuf[4096];



	return TRUE;
}

BOOL FileClient::SendData(LPVOID pData, DWORD nLength)
{
	return 0;
}
