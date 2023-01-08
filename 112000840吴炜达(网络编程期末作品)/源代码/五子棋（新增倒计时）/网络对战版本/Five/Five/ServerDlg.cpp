// ServerDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "Five.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "Table.h"  //�ֶ����
// CServerDlg �Ի���

IMPLEMENT_DYNAMIC(CServerDlg, CDialog)

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
}

CServerDlg::~CServerDlg()
{
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_LISTEN, &CServerDlg::OnClickedBtnListen)
	ON_BN_CLICKED(IDC_BTN_LEAVE, &CServerDlg::OnClickedBtnLeave)
END_MESSAGE_MAP()


// CServerDlg ��Ϣ�������


void CServerDlg::OnClickedBtnListen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTable *pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
    SetDlgItemText( IDC_ST_STATUS, _T("״̬���ȴ�������Ҽ���...") );
    pTable->m_serverSocket.Create( 20000 );
    pTable->m_serverSocket.Listen();
    GetDlgItem( IDC_BTN_LISTEN )->EnableWindow( FALSE );
	GetDlgItem( IDC_BTN_LEAVE )->EnableWindow(TRUE);
}


void CServerDlg::OnClickedBtnLeave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTable *pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
    pTable->m_serverSocket.Close();
	GetDlgItem( IDC_BTN_LISTEN )->EnableWindow(TRUE );
	GetDlgItem( IDC_BTN_LEAVE )->EnableWindow(FALSE);
}


BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
    // ���Ƚ��������ڴﵽģʽ�Ի����Ŀ��
    GetParent()->EnableWindow( FALSE );
    // ��ȡ��������IP��ַ
    CHAR szHost[100];
    CHAR *szIP;
    hostent *host;
    gethostname(szHost, 100);
    SetDlgItemText( IDC_EDIT_HOST, (LPCTSTR)szHost );
    host = gethostbyname( szHost );
    for ( int i = 0; host != NULL && host->h_addr_list[i] != NULL; i++ )
    {
        szIP = inet_ntoa( *( (in_addr *)host->h_addr_list[i] ) );
        break;
    }
    SetDlgItemText( IDC_EDIT_IP, (LPCTSTR)szIP );

    GetDlgItem( IDC_BTN_LISTEN )->SetFocus();
	return FALSE; // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
