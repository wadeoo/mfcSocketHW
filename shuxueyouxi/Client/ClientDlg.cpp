

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include <vector>

#pragma warning(disable: 4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_MYSOCKET WM_USER+1
#define ID_TIMER_1 1
#define ID_TIMER_2 2
#define ID_TIMER_3 3


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()





CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
	, m_login(("no name"))
	, m_port(3600)
	, m_ip(_T("127.0.0.1"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_socket = INVALID_SOCKET;

	r.SetMessage(m_login, m_ip);

}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_login);
	DDX_Text(pDX, IDC_EDIT6, m_port);
	DDV_MinMaxInt(pDX, m_port, 1, 65535);
	DDX_Text(pDX, IDC_EDIT7, m_ip);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CClientDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_BUTTON3, &CClientDlg::OnBnClickededEnter)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CONTINUE, &CClientDlg::OnBnClickedContinue)
END_MESSAGE_MAP()



BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	ha = LoadAccelerators(AfxGetResourceHandle(),MAKEINTRESOURCE(IDR_ACCELERATOR1));
	WSADATA data;

	int rc;
	if ((rc = WSAStartup(MAKEWORD(1, 1), &data)) != 0){
		CString str;
		str.Format(_T("WSAStartup  Error = %d"), WSAGetLastError());
		MessageBox(str);
		EndDialog(IDCANCEL);
		return FALSE;
	}
	
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_INFOTIP | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE);
	//new
	m_list.InsertColumn(0, "a", LVCFMT_CENTER, 200);
	m_list.InsertColumn(1, "r", LVCFMT_CENTER, 70);

	return TRUE;  
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cyIcon = GetSystemMetrics(SM_CYICON);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClientDlg::OnBnClickedConnect()
{
	if (!UpdateData(TRUE)) return;

	OnBnClickedDisconnect();
	if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET){
		CString str;
		str.Format(_T("Socket Error: %d"), WSAGetLastError());
		MessageBox(str);
		return;
	}

	SOCKADDR_IN CAddress;
	int CAddress_len = sizeof(CAddress);
	CAddress.sin_family = AF_INET;
	CAddress.sin_port = htons(m_port);
	CAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(m_socket, (SOCKADDR*) &CAddress, CAddress_len)< 0){
		OnBnClickedDisconnect();
		CString str;
		str.Format(_T("Socket Error: %d"), WSAGetLastError());
		MessageBox(str);
		return;
	}

	WSAAsyncSelect(m_socket, this->m_hWnd, WM_MYSOCKET, FD_READ | FD_CLOSE);

	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	r.SetMessage(m_login, m_ip, 0, 0);
	if (send(m_socket, (char*)&r, sizeof(r), MSG_OOB) == SOCKET_ERROR){
		CString str;
		str.Format("Socket Error: %d", WSAGetLastError());
		MessageBox(str);
		return;
	}

	delete g;
	g = new Game();
	NewLevel();
}

void CClientDlg::NewLevel()
{
	g->level++;
	CString str;
	str.Format("%s%d", "lvl: ", g->level);
	//new
	//GetDlgItem(IDC_LEVEL)->SetWindowTextA(str);
	GetDlgItem(IDC_LEVEL)->SetWindowTextA(str);
	str.Format("%s%d", ": ", g->points);
	GetDlgItem(IDC_COUNT)->SetWindowTextA(str);
	g->sec = 30;
	str.Format("%s%d", "time:", g->sec);
	GetDlgItem(IDC_TIMESEC)->SetWindowTextA(str);

	SetTasks();
	OnEllements();

	SetTimer(ID_TIMER_1, 3000, NULL);
	SetTimer(ID_TIMER_2, 32000, NULL);
	SetTimer(ID_TIMER_3, 1000, NULL);
}

void CClientDlg::OnBnClickedDisconnect()
{
	if (m_socket != INVALID_SOCKET){
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	OffEllements();
	KillTimer(ID_TIMER_1);
	KillTimer(ID_TIMER_2);
	KillTimer(ID_TIMER_3);
}

void CClientDlg::OffEllements()
{
	GetDlgItem(IDC_EDIT5)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(FALSE);
	GetDlgItem(IDC_TIMESEC)->ShowWindow(FALSE);
	GetDlgItem(IDC_COUNT)->ShowWindow(FALSE);
	GetDlgItem(IDC_LEVEL)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(FALSE);
	GetDlgItem(IDC_LABEL_ANSWER)->ShowWindow(FALSE);
	GetDlgItem(IDC_WAITUSERS)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST1)->ShowWindow(FALSE);
	GetDlgItem(IDC_CONTINUE)->ShowWindow(FALSE);
}

void CClientDlg::OnEllements()
{
	GetDlgItem(IDC_EDIT5)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(TRUE);
	GetDlgItem(IDC_TIMESEC)->ShowWindow(TRUE);
	GetDlgItem(IDC_COUNT)->ShowWindow(TRUE);
	GetDlgItem(IDC_LEVEL)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(TRUE);
	GetDlgItem(IDC_LABEL_ANSWER)->ShowWindow(TRUE);
}

void CClientDlg::OnBnClickededEnter()
{
	if (!g) return;
	int k;
	CString str;
	GetDlgItem(IDC_EDIT5)->GetWindowTextA(str);
	if (str){
		GetDlgItem(IDC_EDIT5)->SetWindowTextA("");
		if (k = g->check(_ttoi (str))){
			KillTimer(ID_TIMER_1);
			g->points += 5;
			str.Format("%s%d", "zh", g->points);
			GetDlgItem(IDC_COUNT)->SetWindowTextA(str);
			g->Digits(k - 1);
			g->Operation(k - 1);
			str.Format("%d%c%d", g->x[k - 1], g->getOperation(g->k[k - 1]), g->y[k - 1]);
			GetDlgItem(IDC_EDIT2 + k - 1)->SetWindowTextA(str);
			SetTimer(ID_TIMER_1, 3000, NULL);
		}
	}
}

void CClientDlg::SetTasks()
{
	g->setValues();
	CString str;
	for (int i = 0; i < g->countTasks; i++){
		str.Format("%d%c%d", g->x[i], g->getOperation(g->k[i]), g->y[i]);
		GetDlgItem(IDC_EDIT2+i)->SetWindowTextA(str);
	}
}

void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) SetTasks();
	if (nIDEvent == 2){
		KillTimer(ID_TIMER_1);
		KillTimer(ID_TIMER_2);
		KillTimer(ID_TIMER_3);

		r.SetMessage(m_login, m_ip, g->points, true);
		if (send(m_socket, (char*)&r, sizeof(r), MSG_OOB) == SOCKET_ERROR){
			CString str;
			str.Format(_T("Socket Error: %d"), WSAGetLastError());
			MessageBox(str);
		}

		OffEllements();
		GetDlgItem(IDC_WAITUSERS)->ShowWindow(TRUE);
	}
	if (nIDEvent == 3){
		CString str;
		str.Format("%s%d","time:", g->sec);
		GetDlgItem(IDC_TIMESEC)->SetWindowTextA(str);
		g->sec--;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CClientDlg::OnBnClickedContinue()
{
	GetDlgItem(IDC_CONTINUE)->ShowWindow(FALSE);
	GetDlgItem(IDC_LIST1)->ShowWindow(FALSE);
	NewLevel();
}


BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	if (TranslateAccelerator(m_hWnd, ha, pMsg)) return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


LRESULT CClientDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_MYSOCKET){
		DWORD event = WSAGETSELECTEVENT(lParam);

		if (event == FD_READ){
			reply all_r;
			if (recv(m_socket, (char*)&all_r, sizeof(all_r), 0) == SOCKET_ERROR){
				CString str;
				str.Format("Socket Error: %d", WSAGetLastError());
				MessageBox(str);
				return CDialogEx::WindowProc(message, wParam, lParam);
			}

			if (!all_r.con) m_list.DeleteAllItems();
			CString str;
			int pos = m_list.InsertItem(m_list.GetItemCount(), all_r.name);
			str.Format("%d", all_r.message);
			m_list.SetItemText(pos, 1, str);

			GetDlgItem(IDC_WAITUSERS)->ShowWindow(FALSE);
			GetDlgItem(IDC_LIST1)->ShowWindow(TRUE);
			g->level == 5 ? GetDlgItem(IDC_CONTINUE)->ShowWindow(FALSE) : GetDlgItem(IDC_CONTINUE)->ShowWindow(TRUE);
		}
		else if (event == FD_CLOSE){
			OnBnClickedDisconnect();
			MessageBox("连接中断");
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
