// ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Five.h"
#include "ClientDlg.h"
#include "afxdialogex.h"


// CClientDlg �Ի���

IMPLEMENT_DYNAMIC(CClientDlg, CDialog)

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{

	m_nTimer = 0;
}

CClientDlg::~CClientDlg()
{
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CClientDlg::OnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_OUT, &CClientDlg::OnClickedBtnOut)
	ON_EN_UPDATE(IDC_EDIT_HOST, &CClientDlg::OnUpdateEditHost)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CClientDlg ��Ϣ�������

void CClientDlg::OnClickedBtnConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 CString strHost;

    // ��ȡ��������
    GetDlgItemText( IDC_EDIT_HOST, strHost );
    // ���ó�ʱʱ��
    m_nTimer = 5;
    // ��ʼ������״̬
    m_pTable->m_bConnected = FALSE;
    // ���ÿؼ���Ч״̬
    GetDlgItem( IDC_BTN_CONNECT )->EnableWindow( FALSE );
    GetDlgItem( IDC_EDIT_HOST )->EnableWindow( FALSE );
    // �����׽��ֲ�����
    m_pTable->m_clientSocket.Create();
    m_pTable->m_clientSocket.Connect( strHost, 20000 );
    // ��ʼ��ʱ
    SetTimer( 1, 1000, NULL );
}


void CClientDlg::OnClickedBtnOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer( 1 );
	OnCancel();
}


void CClientDlg::OnUpdateEditHost()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	    // ���������������ʹ�����ӡ���ťʧЧ
	CString str;
    GetDlgItemText( IDC_EDIT_HOST, str );
    GetDlgItem( IDC_BTN_CONNECT )->EnableWindow( !str.IsEmpty() );
}


BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText( IDC_ST_TIMER, _T("") );
    m_pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		if ( 1 == nIDEvent )
    {
        if ( m_pTable->m_bConnected )
        {
            KillTimer( 1 );
            EndDialog( IDOK );
        }
        else if ( 0 == m_nTimer )
        {
            KillTimer( 1 );
            MessageBox( _T("���ӶԷ�ʧ�ܣ�������������IP��ַ�Ƿ���ȷ���Լ����������Ƿ�������"),
                _T("����ʧ��"), MB_ICONERROR );
            SetDlgItemText( IDC_ST_TIMER, _T("") );
            GetDlgItem( IDC_EDIT_HOST )->EnableWindow();
            SetDlgItemText( IDC_EDIT_HOST, _T("") );
            GetDlgItem( IDC_EDIT_HOST )->SetFocus();
        }
        else
        {
            CString str;
            str.Format( _T("��������...(%d)"), m_nTimer-- );
            SetDlgItemText( IDC_ST_TIMER, str);
        }
    }
	CDialog::OnTimer(nIDEvent);
}


void CClientDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	// ����OnOK��ʹ���س���ʱ���˳�
	CDialog::OnOK();
}
