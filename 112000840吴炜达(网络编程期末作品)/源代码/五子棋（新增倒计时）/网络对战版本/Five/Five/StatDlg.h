#pragma once
// CStatDlg �Ի���

class CStatDlg : public CDialog
{
	DECLARE_DYNAMIC(CStatDlg)
	void ShowStat(void);
public:
	CStatDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatDlg();

// �Ի�������
	enum { IDD = IDD_DLG_STAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnClickedBtnReset();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
