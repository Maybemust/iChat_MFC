#pragma once
class FileClient
{
public:
	FileClient();
	~FileClient();
public:
	// ��ʼ���ļ��ͻ���
	BOOL Init();
	// ���ӷ�����
	BOOL ConnectServer(LPCSTR lpServerIP);
	// �����ļ�
	BOOL SendFile(LPCSTR pszFilePath, CProgressCtrl* pWndProgress = NULL);
	// ��������
	BOOL SendData(LPVOID pData, DWORD nLength);

public:
	SOCKET m_ClientSocket;  // �ͻ���socket
};

