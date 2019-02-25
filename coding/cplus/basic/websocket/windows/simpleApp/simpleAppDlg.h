
// simpleAppDlg.h : header file
//

#pragma once


// CsimpleAppDlg dialog
class CsimpleAppDlg : public CDialogEx
{
// Construction
public:
	CsimpleAppDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SIMPLEAPP_DIALOG };

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
	afx_msg void OnDestroy();
protected:
	afx_msg LRESULT OnRecv(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnClickedButton1();
};
