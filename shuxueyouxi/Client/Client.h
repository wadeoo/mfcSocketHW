

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH"
#endif

#include "resource.h"		

class CClientApp : public CWinApp
{
public:
	CClientApp();

	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CClientApp theApp;