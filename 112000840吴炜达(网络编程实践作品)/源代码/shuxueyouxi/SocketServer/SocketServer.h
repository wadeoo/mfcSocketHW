

#pragma once

#ifndef __AFXWIN_H__
	#error " PCH"
#endif

#include "resource.h"		


// CSocketServerApp:
//

class CSocketServerApp : public CWinApp
{
public:
	CSocketServerApp();

public:
	virtual BOOL InitInstance();


	DECLARE_MESSAGE_MAP()
};

extern CSocketServerApp theApp;