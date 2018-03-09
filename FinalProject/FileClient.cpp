#include "stdafx.h"
#include "FileClient.h"
#include <winsock2.h>

#pragma comment(lib,"WS2_32.lib")

CFileClient::CFileClient()
{
	m_ClientSocket = INVALID_SOCKET;
}


CFileClient::~CFileClient()
{
	if (m_ClientSocket != INVALID_SOCKET)
	{
		::closesocket(m_ClientSocket);
		::WSACleanup();
	}
}

BOOL CFileClient::Init()
{
	// ��ʼ��WS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	::WSAStartup(sockVersion, &wsaData);
	// ����socket
	m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_ClientSocket == INVALID_SOCKET)
	{
		AfxMessageBox(_T("Failed socket() for File Client"));
		return FALSE;
	}
	return TRUE;
}

BOOL CFileClient::ConnectServer(LPCSTR lpServerIP)
{
	// ���ӷ�����
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_FILESERVICE);
	addr.sin_addr.S_un.S_addr = inet_addr(lpServerIP);
	if (connect(m_ClientSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("File connect()"));
		return FALSE;
	}

	return TRUE;
}

BOOL CFileClient::SendFile(LPCSTR pszFilePath, CProgressCtrl * pWndProgress)
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
	strcpy(sendFile.szFileName, file.GetFileName());
	sendFile.dwFileLength = file.GetLength();
	SendData(&sendFile, sizeof(sendFile));

	if (pWndProgress != NULL)
	{
		pWndProgress->SetRange32(0, sendFile.dwFileLength);
	}
	// �����ļ�����
	CHAR szBuf[4096];
	DWORD nRemain = file.GetLength();
	while (nRemain > 0)
	{
		// ���㷢����
		DWORD nSend = 4096 < nRemain ? 4096 : nRemain;

		// ��ȡ����
		file.Read(szBuf, nSend);

		// ��������
		SendData(szBuf, nSend);

		// ����ʣ����
		nRemain -= nSend;

		// ���ý�����λ��
		if (pWndProgress != NULL)
		{
			pWndProgress->SetPos(sendFile.dwFileLength - nRemain);
		}
	}

	// �ر��ļ�
	file.Close();
	return TRUE;
}

BOOL CFileClient::SendData(LPVOID pData, DWORD nLength)
{
	LPSTR pTemp = (LPSTR)pData;
	int nRemain = nLength;

	while (nRemain > 0)
	{
		int nSend = send(m_ClientSocket, pTemp, nRemain, 0);
		if (nSend == SOCKET_ERROR)
		{
			AfxMessageBox(_T("Failed send()"));
			return FALSE;
		}
		nRemain -= nSend;

		// ���offset
		pTemp += nSend;
	}

	return TRUE;
}
