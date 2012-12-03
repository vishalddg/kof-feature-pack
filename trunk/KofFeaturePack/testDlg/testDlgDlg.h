
// testDlgDlg.h : header file
//

#pragma once
#include "kofmfccolorbutton.h"
#include "kofmfcspinbuttonctrl.h"
#include "kofmfcmenubutton.h"
#include "afxbutton.h"


// CtestDlgDlg dialog
class CtestDlgDlg : public CKofDialogEx
{
// Construction
public:
	CtestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_TESTDLG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMenu m_menu;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo2();
	CKofMFCFontComboBox m_ComboFont;
	CKofMFCColorButton m_BtnColor;
	CKofMFCMenuButton m_BtnMenu;
	afx_msg void OnBnClickedButton2();
	CMFCLinkCtrl m_BtnLink;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
};
