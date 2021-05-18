
// Chapter8Dlg.h : header file
//

#pragma once
#define WM_TRAY_NOTIFY WM_USER + 0
#define INTERVAL 15
#define WEATHER_SOURCE _T("file:Weather.htm")


// CChapter8Dlg dialog
class CChapter8Dlg : public CDialogEx
{
// Construction
public:
	CChapter8Dlg(CWnd* pParent = NULL);	// standard constructor
	LRESULT OnTrayNotify(WPARAM wParam, LPARAM lParam);
	void ParseHtml(const CString& sHTML);
	void Update();
	void OnMenuWeb();
	void OnMenuExit();
	NOTIFYICONDATA m_nTrayData;
	int m_nTerms;
	CString m_sTerm[50];
	int m_nTermIcon[50];
	CString m_sConditions;
	BOOL m_bHidden;
	BOOL m_bUpdating;
	int m_nIcon;
	BOOL m_bMatch;

// Dialog Data
	enum { IDD = IDD_CHAPTER8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
