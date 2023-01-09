

#pragma once
#include "Game.h"
#include "afxcmn.h"
#include "reply.h"

class CClientDlg : public CDialogEx
{
public:
	CClientDlg(CWnd* pParent = NULL);	
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

protected:
	HICON m_hIcon;

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HACCEL ha;
	SOCKET m_socket;
	CString m_login;
	int m_port;
	CString m_ip;
	void SetTasks();
	void OffEllements();
	void OnEllements();
	void NewLevel();
	Game *g;
	reply r;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickededEnter();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedContinue();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CListCtrl m_list;
	BOOL OnInitDialog();
};
