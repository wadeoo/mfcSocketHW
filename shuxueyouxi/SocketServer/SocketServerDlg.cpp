

#include "stdafx.h"
#include "SocketServer.h"
#include "SocketServerDlg.h"
#include "afxdialogex.h"

#pragma warning(disable: 4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_MYSOCKET WM_USER+1



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


CSocketServerDlg::CSocketServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketServerDlg::IDD, pParent)
	, m_port(3600)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_socket = INVALID_SOCKET;
}

void CSocketServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_port);
	DDV_MinMaxInt(pDX, m_port, 1, 65535);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CSocketServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CSocketServerDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CSocketServerDlg::OnBnClickedStop)
END_MESSAGE_MAP()



BOOL CSocketServerDlg::OnInitDialog()
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

	WSADATA data;

	int rc;
	if( (rc = WSAStartup (MAKEWORD(1, 1), &data)) != 0){
		CString str;
		str.Format(L"WSAStartup  Error = %d", WSAGetLastError());
		MessageBox(str);
		EndDialog(IDCANCEL);
		return FALSE;
	}

	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_INFOTIP | LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE);
	m_list.InsertColumn(0, L"用户", LVCFMT_CENTER, 200);
	m_list.InsertColumn(1, L"账号",LVCFMT_CENTER, 200);

	return TRUE;  
}

void CSocketServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CSocketServerDlg::OnPaint()
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

HCURSOR CSocketServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSocketServerDlg::OnBnClickedStart()
{
	if (!UpdateData(TRUE)) return;

	OnBnClickedStop();
	if((m_socket=socket(AF_INET, SOCK_STREAM, 0))  == INVALID_SOCKET){
		CString str;
		str.Format(L"Socket Error = %d", WSAGetLastError());
		MessageBox(str);
		return;
	}

	SOCKADDR_IN CAddress;
	CAddress.sin_family = AF_INET;
	CAddress.sin_port = htons(m_port);
	CAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(m_socket, (SOCKADDR*)&CAddress, sizeof(CAddress)) == SOCKET_ERROR){
		CString str;
		str.Format(L"Socket Error = %d", WSAGetLastError());
		MessageBox(str);
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return;
	}

	WSAAsyncSelect(m_socket, this->m_hWnd, WM_MYSOCKET, FD_ACCEPT | FD_READ | FD_CLOSE);

	if(listen(m_socket, 1) == SOCKET_ERROR){ 
		CString str;
		str.Format(L"Socket Error = %d", WSAGetLastError());
		MessageBox(str);
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return;
	}

	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
}


void CSocketServerDlg::OnBnClickedStop()
{
	if (m_socket != INVALID_SOCKET){
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
	}
	s_clients.clear();
	all_r.clear();

	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
}

LRESULT CSocketServerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_MYSOCKET){
		DWORD event = WSAGETSELECTEVENT(lParam);
		SOCKET s_client = (SOCKET)wParam;
		sockaddr_in CAddress = { 0 };
		int CAddress_len = sizeof(CAddress);

		if (event == FD_ACCEPT){
			s_clients.push_back(accept(m_socket, (LPSOCKADDR)&CAddress, &CAddress_len));
			CString str;
			str.Format(L"Accept: %d.%d.%d.%d", CAddress.sin_addr.S_un.S_un_b.s_b1, CAddress.sin_addr.S_un.S_un_b.s_b2, CAddress.sin_addr.S_un.S_un_b.s_b3, CAddress.sin_addr.S_un.S_un_b.s_b4);
			m_list.InsertItem(m_list.GetItemCount(), str);
		}
		else if (event == FD_READ){
			getsockname(s_client, (LPSOCKADDR)&CAddress, &CAddress_len);
			reply r;
			CString str;

			if (recv(s_client, (char*)&r, sizeof(r), 0) == SOCKET_ERROR){
				str.Format(L"Socket Error: %d", WSAGetLastError());
				MessageBox(str);
				return CDialogEx::WindowProc(message, wParam, lParam);
			}

			str.Format(L"用户: %s", r.name);
			int pos = m_list.InsertItem(m_list.GetItemCount(), str);

			if (r.con){
				str.Format(L"%d", r.message);
				m_list.SetItemText(pos, 1, str);
				all_r.push_back(r);
			}
			else m_list.SetItemText(pos, 1, L"connected to game");

			if (all_r.size() && all_r.size() == s_clients.size()){
				all_r[0].con = false;
				for (int i = 0; i < s_clients.size(); i++)
					for (int j = 0; j < all_r.size(); j++){
						if (send(s_clients[i], (char*)&all_r[j], sizeof(all_r[j]), MSG_OOB) == SOCKET_ERROR){
							str.Format(_T("Socket Error: %d"), WSAGetLastError());
							MessageBox(str);
							return CDialogEx::WindowProc(message, wParam, lParam);
						}
						Sleep(100);
					}
				all_r.clear();
			}
		}
		else if (event == FD_CLOSE){
			getsockname(s_client, (LPSOCKADDR)&CAddress, &CAddress_len);
			CString str;
			str.Format(L"Disconnect: %d.%d.%d.%d", CAddress.sin_addr.S_un.S_un_b.s_b1, CAddress.sin_addr.S_un.S_un_b.s_b2, CAddress.sin_addr.S_un.S_un_b.s_b3, CAddress.sin_addr.S_un.S_un_b.s_b4);
			m_list.InsertItem(m_list.GetItemCount(), str);
			
			str.Format(L"%d.%d.%d.%d", CAddress.sin_addr.S_un.S_un_b.s_b1, CAddress.sin_addr.S_un.S_un_b.s_b2, CAddress.sin_addr.S_un.S_un_b.s_b3, CAddress.sin_addr.S_un.S_un_b.s_b4);
			for (int i = 0; i < all_r.size(); i++)
				if (all_r[i].ip == str) all_r.erase(all_r.begin() + i);
			for (int i = 0; i < s_clients.size(); i++)
				if (s_client == s_clients[i]) s_clients.erase(s_clients.begin() + i);
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}
