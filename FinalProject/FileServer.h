#pragma once
class CFileServer
{
public:
	CFileServer();
	~CFileServer();

public:
	// ��ʼ���ļ�������
	BOOL Init();
	// ���տͻ������ӵ��߳�
	static UINT FileThread(LPVOID pParam);
	// ��������
	void OnConnect(SOCKET ClientSocket, LPSTR pszIP);

public:
	SOCKET m_ServerSocket;
};

