#pragma once


// FileReceive �Ի���

class FileReceive : public CDialog
{
	DECLARE_DYNAMIC(FileReceive)

public:
	FileReceive(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FileReceive();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RECEIVE };
#endif

private:
	CStatic       m_Info;				// ������Ϣ
	CProgressCtrl m_wndProgress;		// ������
	SENDFILE      m_SendFile;			// �����ļ�
	CString       m_strFilePath;		// �ļ�·��

public:
	SOCKET        m_ClientSocket;
	CString       m_strIP;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	// �����߳�
	static UINT ReceiveThread(LPVOID pParam);
	// ���ݽ���
	BOOL Receive(LPVOID pData, DWORD nLength);

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
