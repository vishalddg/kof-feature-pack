#pragma once
#include "KofPack.h"
#include "KofDialogEx.h"
#include "KofMFCButton.h"

//////////////////////////////////////////////////////////////////////////
// CKofMessageBox

struct KOFPACKDLLEXPORT KOF_MSGBOXPARAMS : public MSGBOXPARAMS
{
	BOOL    bShowCheckBox;
	BOOL    bShowSeparator;
	LPCTSTR lpszCheckBoxText; 
	UINT*   puiAutoRespond;
	BOOL    bIgnoreStandardButtons;

	enum
	{
		UserButtonsCount = 4
	};
	LPCTSTR lpszUserButtonText[UserButtonsCount];
	UINT    uiUserButtonID[UserButtonsCount];

	inline KOF_MSGBOXPARAMS ()
	{
		ZeroMemory (this, sizeof (KOF_MSGBOXPARAMS));
		cbSize = sizeof (MSGBOXPARAMS);
	}
};

//////////////////////////////////////////////////////////////////////////
// CKofMessageBox

class KOFPACKDLLEXPORT CKofMessageBox : public CKofDialogEx
{
	DECLARE_DYNAMIC(CKofMessageBox)

public:
	CKofMessageBox(const MSGBOXPARAMS* pParams);
	CKofMessageBox(const KOF_MSGBOXPARAMS* pParams);
	virtual ~CKofMessageBox();

	static void SetLocalizedString(UINT uID, LPCTSTR lpszText);

protected:
	KOF_MSGBOXPARAMS m_Params;
	DLGTEMPLATE* m_pTemplate;

	HICON   m_hMessageIcon;
	CString m_strMessageCaption;
	CString m_strMessageText;
	CString m_strCheckBox;
	CFont   m_fntText;
	int     m_nDefaultButtonIndex;

	CArray <CWnd*, CWnd*> m_arrButtons;
	CKofMFCButton m_wndDontAskCheckBox;
	bool    m_bHasCancelButton;
	DWORD   m_dwDrawTextFlags;
	CRect   m_rectIcon;
	CRect   m_rectText;
	int     m_cySeparatorLine;
	CPoint  m_ptNextButtonPos;
	bool    m_bRightAlignment;

	// Initial sizes
	CRect   m_rectClientMargins;
	int     m_cxIconSpacing;  // spacing between an icon and message text
	CSize   m_szButton;
	int     m_cyCheckBoxHeight;
	int     m_cxButtonSpacing;  // gap between buttons
	int     m_cyVerticalSpacing; // vertical spacing between text, optional check box and buttons

	void Initialize();
	void AddButton(UINT id, HINSTANCE hInst, LPCTSTR lpszCaption = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void DrawText(CDC* pDC);
	virtual void PreInitDialog();

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnButton(UINT nID);
	afx_msg LRESULT OnHelp(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};

int KOFPACKDLLEXPORT KofMessageBox (HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
int KOFPACKDLLEXPORT KofMessageBoxIndirect (const MSGBOXPARAMS* pMsgBoxParams);
int KOFPACKDLLEXPORT KofMessageBoxIndirect (const KOF_MSGBOXPARAMS* pMsgBoxParams);

int KOFPACKDLLEXPORT KofMessageBox (LPCTSTR lpszText, UINT nType = MB_OK);
int KOFPACKDLLEXPORT KofMessageBox (UINT nIDPrompt, UINT nType = MB_OK);
