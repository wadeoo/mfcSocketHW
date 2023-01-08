// FiveDlg.h : ͷ�ļ�
#pragma once
#include "Table.h"
#include "FiveSocket.h" //�ֶ����
#include "afxwin.h"

// CFiveDlg �Ի���
class CFiveDlg : public CDialogEx
{
// ����
public:
	CDialog * m_pDlg;
	CTable m_Table;
	CFiveDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FIVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuPlayerfirst();
	afx_msg void OnMenuPcfirst();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnMenuServer();
	afx_msg void OnMenuClient();
	afx_msg void OnMenuPlayagain();
	afx_msg void OnMenuLeave();
	afx_msg void OnMenuName();
	afx_msg void OnMenuStat();
	afx_msg void OnClickedBtnQhq();
	afx_msg void OnClickedBtnLost();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_ChatList;
	HWND m_hChat;
	CString m_strChat;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CStatic cdTime;
};
