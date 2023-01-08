// FiveDlg.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Five.h"
#include "FiveDlg.h"
#include "afxdialogex.h"

#include "ServerDlg.h"
#include "ClientDlg.h"
#include "NameDlg.h"
#include "StatDlg.h"
#include "Table.h"

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// �Ի�������
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{ }

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CFiveDlg �Ի���
CFiveDlg::CFiveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFiveDlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strChat = _T("");
}

void CFiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDT_CHAT, m_ChatList);
	DDX_CBString(pDX, IDC_CMB_CHAT, m_strChat);
	DDX_Control(pDX, IDC_STATIC1, cdTime);
}

BEGIN_MESSAGE_MAP(CFiveDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_ABOUT, &CFiveDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_PlayerFirst, &CFiveDlg::OnMenuPlayerfirst)
	ON_COMMAND(ID_MENU_PCFirst, &CFiveDlg::OnMenuPcfirst)
	ON_BN_CLICKED(IDC_BTN_BACK, &CFiveDlg::OnBnClickedBtnBack)
	ON_COMMAND(ID_MENU_SERVER, &CFiveDlg::OnMenuServer)
	ON_COMMAND(ID_MENU_CLIENT, &CFiveDlg::OnMenuClient)
	ON_COMMAND(ID_MENU_PLAYAGAIN, &CFiveDlg::OnMenuPlayagain)
	ON_COMMAND(ID_MENU_LEAVE, &CFiveDlg::OnMenuLeave)
	ON_COMMAND(ID_MENU_NAME, &CFiveDlg::OnMenuName)
	ON_COMMAND(ID_MENU_STAT, &CFiveDlg::OnMenuStat)
	ON_BN_CLICKED(IDC_BTN_QHQ, &CFiveDlg::OnClickedBtnQhq)
	ON_BN_CLICKED(IDC_BTN_LOST, &CFiveDlg::OnClickedBtnLost)
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_TIMER()
	ON_WM_TIMER()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFiveDlg ��Ϣ�������
BOOL CFiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_pDlg = NULL;
    CRect rect(0, 0, 200, 200);
    m_Table.CreateEx( WS_EX_CLIENTEDGE, _T("ChessTable"), NULL, WS_VISIBLE | WS_BORDER | WS_CHILD,
        CRect( 0, 0, 480, 509 ), this, IDC_TABLE );
    // ����˫������
    SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    SetDlgItemText( IDC_ST_ENEMY, _T("�����") );
    // ���á����桱�͡��뿪��
    CMenu *pMenu = GetMenu();
    pMenu->EnableMenuItem( ID_MENU_PLAYAGAIN, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );
    pMenu->EnableMenuItem( ID_MENU_LEAVE, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND );

	m_Table.Clear( TRUE );
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );

	//��������Ϊ�����ս��������
	 // �����������������������س�ʹ��
	m_hChat = (HWND)FindWindowEx( GetDlgItem( IDC_CMB_CHAT )->GetSafeHwnd(), NULL, _T("Edit"), NULL );
	 ::SendMessage( m_hChat, EM_LIMITTEXT, (WPARAM)128, 0);
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );  
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );

	GetDlgItem(IDC_TABLE)->SetFocus();
	return FALSE;  // ���ǽ��������õ��ؼ������򷵻�TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CFiveDlg::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CFiveDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//���ڶԻ���
void CFiveDlg::OnMenuAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
    dlg.DoModal();
}
//�������
void CFiveDlg::OnMenuPlayerfirst()
{
	// TODO: �ڴ���������������
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// ����Զ��ģ���������塢����������
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	m_Table.Accept( 1 );
}

//���������
void CFiveDlg::OnMenuPcfirst()
{
	// TODO: �ڴ���������������
	GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
	// ����Զ��ģ���������塢����������
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
	m_Table.SetColor( 1 );
    m_Table.Clear( FALSE );
    m_Table.SetGameMode( 1 );
}
//����
void CFiveDlg::OnBnClickedBtnBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 m_Table.Back();
}


void CFiveDlg::OnMenuServer()
{
	// TODO: �ڴ���������������
	m_pDlg = new CServerDlg;
    m_pDlg->Create( IDD_DLG_SERVER, this );
    m_pDlg->ShowWindow( SW_SHOW );
}


void CFiveDlg::OnMenuClient()
{
	// TODO: �ڴ���������������
    CClientDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        // ���ͼ�������
        MSGSTRUCT msg;
        msg.uMsg = MSG_OPPOSITE;
        lstrcpy( msg.szMsg, m_Table.m_strMe );

        m_Table.m_clientSocket.Send( (LPCVOID)&msg, sizeof( MSGSTRUCT ) );
        // ���ð�ť״̬
        GetDlgItem( IDC_BTN_QHQ )->EnableWindow( TRUE );
        GetDlgItem( IDC_CMB_CHAT )->EnableWindow( TRUE );
        GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
        GetDlgItem( IDC_BTN_LOST )->EnableWindow( TRUE );
        // ���ò˵�״̬
        m_Table.SetMenuState( FALSE );
    }
}


void CFiveDlg::OnMenuPlayagain()
{
	// TODO: �ڴ���������������
    m_Table.PlayAgain();
}


void CFiveDlg::OnMenuLeave()
{
	// TODO: �ڴ���������������
	m_Table.m_serverSocket.Close();
    GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
    GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    // ���ò˵�״̬
    m_Table.SetMenuState( TRUE );
    // �������̵ȴ�״̬
    m_Table.SetWait( TRUE );
    // ������������״̬
    m_Table.m_bConnected = FALSE;
    // �������öԷ�����
    SetDlgItemText( IDC_ST_ENEMY, _T("����Ҽ���") );
}


void CFiveDlg::OnMenuName()
{
	// TODO: �ڴ���������������
	CNameDlg dlg;
    if ( IDOK == dlg.DoModal() )
    {
        SetDlgItemText( IDC_ST_ME, m_Table.m_strMe );
    }
}


void CFiveDlg::OnMenuStat()
{
	// TODO: �ڴ���������������
	CStatDlg dlg;
    dlg.DoModal();
}


void CFiveDlg::OnClickedBtnQhq()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Table.DrawGame();
}


void CFiveDlg::OnClickedBtnLost()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
		m_Table.GiveUp();
}


BOOL CFiveDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if ( GetDlgItem( IDC_EDT_CHAT ) == pWnd )
    {
        // ���������¼�����ָ��
        SetCursor( LoadCursor( NULL, IDC_ARROW ) );
        return TRUE;
    }
    else
		return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CFiveDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	  // �����������봰�ڵĻس���Ϣ
	    UpdateData(TRUE);
        // ������������
        m_Table.Chat( m_strChat );
        // ���������¼
        CString strAdd;
        strAdd.Format( _T("�� ˵��%s\r\n"), m_strChat );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // ����������봰��
        m_strChat="";
		UpdateData(FALSE);
}


BOOL CFiveDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam && m_hChat == pMsg->hwnd )
    {
        // �����������봰�ڵĻس���Ϣ
        TCHAR str[128];
        // ������������
        ::GetWindowText( m_hChat, str, 128 );
        m_Table.Chat( str );
        // ���������¼
        CString strAdd;
        strAdd.Format( _T("�� ˵��%s\r\n"), str );
        m_ChatList.SetSel( -1, -1, TRUE );
        m_ChatList.ReplaceSel( strAdd );
        // ����������봰��
        ::SetWindowText( m_hChat, _T("") );
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}
void CFiveDlg::OnCancel() 
{
    if ( IDYES == MessageBox( _T("ȷ��Ҫ�˳���"), _T("������"), MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2 ) )
        CDialog::OnCancel();
}







void CFiveDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	switch (nIDEvent) {
	case 50:
		m_Table.m_cdNumber--;
		str.Format(_T("%i"), m_Table.m_cdNumber);
		cdTime.SetWindowText(str);
		if (m_Table.m_cdNumber == 0) {
			KillTimer(nIDEvent);
			m_Table.m_cdNumber = 14;
			str.Format(_T("%i"), m_Table.m_cdNumber);
			cdTime.SetWindowText(str);
			//ʱ�䵽��֮������
			m_Table.GiveUp();
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}
