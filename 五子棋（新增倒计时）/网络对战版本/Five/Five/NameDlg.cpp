// NameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Five.h"
#include "NameDlg.h"
#include "afxdialogex.h"
#include "Table.h" //�ֶ����

// CNameDlg �Ի���

IMPLEMENT_DYNAMIC(CNameDlg, CDialog)

CNameDlg::CNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNameDlg::IDD, pParent)
{

}

CNameDlg::~CNameDlg()
{
}

void CNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNameDlg, CDialog)
	ON_EN_UPDATE(IDC_EDIT_NAME, &CNameDlg::OnUpdateEditName)
END_MESSAGE_MAP()


// CNameDlg ��Ϣ�������


void CNameDlg::OnUpdateEditName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// �������Խ� EM_SETEVENTMASK ��Ϣ���͵��ÿؼ���
	// ͬʱ�� ENM_UPDATE ��־�������㵽 lParam �����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
    GetDlgItemText( IDC_EDIT_NAME, str );
    GetDlgItem( IDOK )->EnableWindow( !str.IsEmpty() );
}


BOOL CNameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CEdit *pEdit = (CEdit *)GetDlgItem( IDC_EDIT_NAME );
    // ��ȡ�������
    CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    ::GetPrivateProfileString( _T("Options"), _T("Name"), _T("Renjiu"), m_strName, 15, pApp->m_szIni );
    // �����ı�����������
    pEdit->LimitText( 15 );
    pEdit->SetWindowText( m_strName );
    pEdit->SetSel( 0, -1 );
    pEdit->SetFocus();
	return FALSE;   // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CNameDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	// д���������
    CFiveApp *pApp = (CFiveApp *)AfxGetApp();
    GetDlgItemText( IDC_EDIT_NAME, m_strName, 10 );
    ::WritePrivateProfileString( _T("Options"), _T("Name"), m_strName, pApp->m_szIni );
    // �����������
    CTable *pTable = (CTable *)GetParent()->GetDlgItem( IDC_TABLE );
    pTable->m_strMe = m_strName;
	CDialog::OnOK();
}
