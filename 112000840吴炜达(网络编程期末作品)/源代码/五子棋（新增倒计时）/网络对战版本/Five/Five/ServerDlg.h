#pragma once

// CServerDlg �Ի���

class CServerDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerDlg)

public:
	CServerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CServerDlg();

// �Ի�������
	enum { IDD = IDD_DLG_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnClickedBtnListen();
	afx_msg void OnClickedBtnLeave();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
