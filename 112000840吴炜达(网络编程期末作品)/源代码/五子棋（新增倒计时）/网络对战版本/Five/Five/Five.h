// Five.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "resource.h"		// ������
// CFiveApp:
// �йش����ʵ�֣������ Five.cpp

class CFiveApp : public CWinApp
{
public:
	CFiveApp();
	TCHAR m_szIni[MAX_PATH];
    int m_nWin;
    int m_nDraw;
    int m_nLost;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFiveApp theApp;