
// Chapter8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chapter8.h"
#include "Chapter8Dlg.h"
#include "afxdialogex.h"
#include "afxinet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CChapter8Dlg dialog




CChapter8Dlg::CChapter8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChapter8Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChapter8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChapter8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_TRAY_NOTIFY, OnTrayNotify)
	ON_COMMAND(IDC_UPDATE, CChapter8Dlg::Update)
	ON_COMMAND(IDC_WEB, CChapter8Dlg::OnMenuWeb)
	ON_COMMAND(IDC_EXIT, CChapter8Dlg::OnMenuExit)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CChapter8Dlg message handlers

BOOL CChapter8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_nTerms = 9;
	m_sTerm[0] = _T("SUNNY");			m_nTermIcon[0] = IDI_SUNNY;
	m_sTerm[1] = _T("CLOUDY");			m_nTermIcon[1] = IDI_CLOUDY;
	m_sTerm[2] = _T("RAIN");			m_nTermIcon[2] = IDI_RAIN;
	m_sTerm[3] = _T("SNOW");			m_nTermIcon[3] = IDI_SNOW;
	m_sTerm[4] = _T("OVERCAST");		m_nTermIcon[4] = IDI_CLOUDY;
	m_sTerm[5] = _T("FOGGY");			m_nTermIcon[5] = IDI_CLOUDY;
	m_sTerm[6] = _T("PARTLY");			m_nTermIcon[6] = IDI_CLOUDY;
	m_sTerm[7] = _T("SLEET");			m_nTermIcon[7] = IDI_RAIN;
	m_sTerm[8] = _T("SHOWERS");			m_nTermIcon[8] = IDI_RAIN;

	ShowWindow(SW_MINIMIZE);
	m_nTrayData.cbSize = sizeof(NOTIFYICONDATA);
	m_nTrayData.hWnd = m_hWnd;
	m_nTrayData.uID = 0;
	m_nTrayData.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_UNKNOWN));
	m_nTrayData.uCallbackMessage = WM_TRAY_NOTIFY;
	wcscpy_s(m_nTrayData.szTip, _T("Chapter8(initializing"));
	m_nTrayData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_nTrayData);
	m_bHidden = false;
	m_bUpdating = false;
	SetTimer(1, 1000, NULL);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChapter8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChapter8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChapter8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CChapter8Dlg::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
	if(lParam == WM_RBUTTONDOWN)
	{
		CMenu menu;
		VERIFY(menu.LoadMenu(IDR_MENU1));
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup!=NULL);
		CRect screen;
		GetDesktopWindow()->GetWindowRect(screen);
		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
								screen.right,
								screen.bottom,
								AfxGetMainWnd());
	}
	return LRESULT(0);
}





void CChapter8Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);

	if(!m_bHidden)
	{
		m_bHidden = true;
		ShowWindow(SW_HIDE);
	}

	Update();
	SetTimer(1, INTERVAL * 60 * 1000, NULL);

	CDialogEx::OnTimer(nIDEvent);
}

void CChapter8Dlg::Update()
{
	if(m_bUpdating)
		return;

	m_bUpdating = true;
	//CRobotInternet internet;
	CString sHtml;
	int nResult;
	CString sErrMsg;
	BOOL bHaveData = false;
	m_bMatch = false;

	CString sURL = WEATHER_SOURCE;

	if(sURL.Left(5) == _T("file:"))
	{
		CStdioFile file;
		CString sLine;
		if(file.Open(sURL.Mid(5), CFile::modeRead))
		{
			sHtml = _T("");
			while(file.ReadString(sLine))
			{
				sHtml += sLine + _T("\n");
			}
			file.Close();
			bHaveData = true;
		}	
	}
	else
	TRY
	{
		CInternetSession session;
		CHttpConnection* pConnection = NULL;
		CHttpFile* pFile1 = NULL;
		char* buffer = new char[10240];
		UINT nBytesRead = 0;

		pConnection = session.GetHttpConnection(WEATHER_SOURCE, 80,_T(""),_T(""));
		pFile1 = pConnection->OpenRequest(_T("GET"), _T("/"));
		pFile1->SendRequest();
		nBytesRead = pFile1->Read(buffer, 10240);
		buffer[nBytesRead] = _T('\0');

			if(pConnection != NULL)
			{
				sHtml = buffer;
			}
			if(pFile1)delete pFile1;
			if(pConnection) delete pConnection;
			delete[] buffer;
	}
	CATCH(CInternetException, ie)
	{
		ie->Delete();
	}
	END_CATCH
	
	if(bHaveData)
	{
		sHtml.MakeUpper();
		ParseHtml(sHtml);
	}

	if(!m_bMatch)
	{
		m_nIcon = IDI_UNKNOWN;
		m_sConditions = _T("UNKNOWN (Internet error)");
	}
	m_nTrayData.hIcon = LoadIcon(AfxGetInstanceHandle(),
								MAKEINTRESOURCE(m_nIcon));
	CString sForecast = _T("Chapter8 - Forecast: ") + m_sConditions;
	sForecast = sForecast.Left(63);
	wcscpy_s(m_nTrayData.szTip, sForecast);
	m_nTrayData.uFlags = NIF_ICON | NIF_TIP;
	Shell_NotifyIcon(NIM_MODIFY, &m_nTrayData);
	m_bUpdating = false;
	
}

void CChapter8Dlg::ParseHtml(const CString& sHTML)
{
	int nPos = 0;
	int nLen = sHTML.GetLength();
		for(int t = 0;t < m_nTerms; t++)
		{
			if(sHTML.Find(m_sTerm[t]) != -1)
			{
				m_nIcon = m_nTermIcon[t];
				m_sConditions = m_sTerm[t];
				m_bMatch = true;
				t = m_nTerms;
				return;
			}
		}
}

void CChapter8Dlg::OnMenuWeb()
{
	//MessageBox(_T("worked"));
	ShellExecute(NULL,
				_T("open"),
				WEATHER_SOURCE,
				NULL,
				NULL,
				SW_SHOWNORMAL
					);
}

void CChapter8Dlg::OnMenuExit()
{
	Shell_NotifyIcon(NIM_DELETE, &m_nTrayData);
	EndDialog(0);
}