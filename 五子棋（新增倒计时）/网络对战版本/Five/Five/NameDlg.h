#pragma once

// CNameDlg �Ի���

class CNameDlg : public CDialog
{
	DECLARE_DYNAMIC(CNameDlg)
	TCHAR m_strName[15];
public:
	CNameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNameDlg();

// �Ի�������
	enum { IDD = IDD_DLG_NAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnUpdateEditName();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
};
