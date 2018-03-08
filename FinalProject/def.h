#pragma once

#include "stdafx.h"

#define PORT_USERSERVICE 8989
#define PORT_FILESERVICE 8990

// ���ݰ��İ�ͷ
typedef struct _tagNetHeader
{
	unsigned long  dwVersion;
	unsigned long  dwCmdID;
	unsigned long  dwDataLength;
}NETHEADER, *LPNETHEADER;

// UDP���ݱ�
typedef struct _tagUDPPacket
{
	NETHEADER	header;
	char		szData[256];
}UDPPACKET, *LPUDPPACKET;

// �û��㲥���ݰ�
#define NETCMDID_USERBROADCAST 1
typedef struct _tagUserBroadcast
{
	NETHEADER	header;
	char		szName[128];
	//CHAR		szSign[128];
}USERBROADCAST, *LPUSERBROADCAST;

// �û������˳����ݰ�
#define NETCMDID_USERQUIT 2
typedef struct _tagUserQuit
{
	NETHEADER	header;
	unsigned long		dwExitCode;
}USERQUIT, *LPUSERQUIT;

// ��������
#define NETCMDID_USERCHAT 3
typedef struct _tagUserChat
{
	NETHEADER	header;
	char		szChat[256];
}USERCHAT, *LPUSERCHAT;

// �����ļ�  
#define  NETCMDID_SENDFILE  4
typedef struct  _tagSendFile
{
	char  szFileName[256];
	unsigned long dwFileLength;
}SENDFILE, *LPSENDFILE;
