#pragma once



// CFileThread

class CFileThread : public CWinThread
{
	DECLARE_DYNCREATE(CFileThread)

protected:
	CFileThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CFileThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


