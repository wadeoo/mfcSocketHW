// Five.cpp : ����Ӧ�ó��������Ϊ��

#include "stdafx.h"
#include "Five.h"
#include "FiveDlg.h"

// CFiveApp

BEGIN_MESSAGE_MAP(CFiveApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFiveApp ����

CFiveApp::CFiveApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CFiveApp ����

CFiveApp theApp;


// CFiveApp ��ʼ��

BOOL CFiveApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	    // ��������ļ�λ��
    ::GetModuleFileName( NULL, m_szIni, MAX_PATH );
    lstrcpy( &m_szIni[lstrlen( m_szIni ) - 3], _T("ini") );
    // ��ȡս��ͳ��
    m_nWin = ::GetPrivateProfileInt( _T("Stats"), _T("Win"), 0, m_szIni );
    m_nDraw = ::GetPrivateProfileInt( _T("Stats"), _T("Draw"), 0, m_szIni );
    m_nLost = ::GetPrivateProfileInt( _T("Stats"), _T("Lost"), 0, m_szIni );
    // ע�����̴�����
    WNDCLASS wc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject( WHITE_BRUSH );
    wc.hCursor = LoadCursor( IDC_ARROW );
    wc.hIcon = NULL;
    wc.hInstance = AfxGetInstanceHandle();
    wc.lpfnWndProc = ::DefWindowProc;
    wc.lpszClassName = _T("ChessTable");
    wc.lpszMenuName = NULL;
    wc.style = 0;
    AfxRegisterClass( &wc );

	CFiveDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

