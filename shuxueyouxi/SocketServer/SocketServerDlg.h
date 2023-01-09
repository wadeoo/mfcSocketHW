

#pragma once
#include "afxcmn.h"
#include "../Client/reply.h"
#include <vector>

class CSocketServerDlg : public CDialogEx
{
public:
	CSocketServerDlg(CWnd* pParent = NULL);	
	enum { IDD = IDD_SOCKETSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	

	SOCKET m_socket;
protected:
	HICON m_hIcon;

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	int m_port;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	CListCtrl m_list;
	std::vector<reply> all_r;
	std::vector<SOCKET> s_clients;
	BOOL OnInitDialog();

};