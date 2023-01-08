// FiveSocket.cpp : ʵ���ļ�
#include "stdafx.h"
#include "Five.h"
#include "FiveSocket.h"
#include "Table.h"  //�ֶ����
#include "FiveDlg.h"   //�ֶ����

// CFiveSocket
CFiveSocket::CFiveSocket() {  }
CFiveSocket::~CFiveSocket() { }

#if 0
BEGIN_MESSAGE_MAP(CFiveSocket, CAsyncSocket)
END_MESSAGE_MAP()
#endif	// 0

// CFiveSocket ��Ա����
void CFiveSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CFiveDlg *pDlg = (CFiveDlg *)AfxGetMainWnd();
    // ʹ��������Ч
    pDlg->EnableWindow();
    delete []pDlg->m_pDlg;
    pDlg->m_pDlg = NULL;
    pDlg->m_Table.Accept( 2 );
    pDlg->GetDlgItem( IDC_BTN_QHQ )->EnableWindow( TRUE );
    pDlg->GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_CMB_CHAT )->EnableWindow( TRUE );
    pDlg->GetDlgItem( IDC_BTN_LOST )->EnableWindow( TRUE );
    pDlg->m_Table.SetMenuState( FALSE );
}

void CFiveSocket::OnConnect(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
    CTable *pTable = (CTable *)AfxGetMainWnd()->GetDlgItem( IDC_TABLE );
    pTable->m_bConnected = TRUE;
    pTable->Connect( 2 );
}

void CFiveSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
    CTable *pTable = (CTable *)AfxGetMainWnd()->GetDlgItem( IDC_TABLE );
    pTable->Receive();
}

void CFiveSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
    CFiveDlg *pDlg = (CFiveDlg *)AfxGetMainWnd();
    pDlg->MessageBox( _T("�Է��Ѿ��뿪��Ϸ�������ٽ������١�"), _T("������"), MB_ICONINFORMATION);
    // ����������Ŀ����ʹ�˵���Ч
    pDlg->GetDlgItem( IDC_BTN_QHQ )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_BTN_BACK )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_CMB_CHAT )->EnableWindow( FALSE );
    pDlg->GetDlgItem( IDC_BTN_LOST )->EnableWindow( FALSE );
    pDlg->m_Table.SetMenuState( TRUE );
    pDlg->GetMenu()->EnableMenuItem( ID_MENU_PLAYAGAIN, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED );
    pDlg->m_Table.SetWait( TRUE );
    // �������öԷ�����
    pDlg->SetDlgItemText( IDC_ST_ENEMY, _T("����Ҽ���") );
}
