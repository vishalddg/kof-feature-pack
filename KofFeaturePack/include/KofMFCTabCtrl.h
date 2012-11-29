#pragma once
#include "KofPack.h"

/////////////////////////////////////////////////////////////////////////////
// CKofMFCTabInfo

class CKofMFCTabInfo : public CObject
{
	friend class CMFCTabCtrl;
	friend class CMFCBaseTabCtrl;
	friend class CMFCOutlookBarTabCtrl;
	friend class CKofMFCTabCtrl;

	CKofMFCTabInfo(const CString& strText, const UINT uiIcon, CWnd* pWnd, const int iTabID, BOOL bDetachable) :
	m_pWnd(pWnd), m_uiIcon(uiIcon), m_iTabID(iTabID), m_bIsDetachable(bDetachable)
	{
		m_strText = strText;
		m_rect.SetRectEmpty();
		m_bVisible = TRUE;
		m_nFullWidth = 0;
		m_hIcon = NULL;
		m_bIconOnly = FALSE;
		m_bAlwaysShowToolTip = FALSE;

		m_clrText = (COLORREF) -1;
		m_clrBack = (COLORREF) -1;

		if (m_pWnd != NULL)
		{
			TCHAR szClass [256];
			::GetClassName(m_pWnd->GetSafeHwnd(), szClass, 255);

			CString strClass = szClass;
			m_bIsListView = (strClass == _T("SysListView32"));
		}
		else
		{
			m_bIsListView = FALSE;
		}
	}

	~CKofMFCTabInfo()
	{
		if (m_hIcon != NULL)
		{
			::DestroyIcon(m_hIcon);
		}
	}

	CString   m_strText;
	UINT      m_uiIcon;
	HICON     m_hIcon;
	CRect     m_rect;
	CWnd*     m_pWnd;
	int       m_nFullWidth;
	const int m_iTabID;

	COLORREF m_clrText;
	COLORREF m_clrBack;

	BOOL m_bVisible;
	BOOL m_bIsListView;
	BOOL m_bIconOnly;
	BOOL m_bAlwaysShowToolTip;
	BOOL m_bIsDetachable;

public:
	CRect GetRect() const { return m_rect; }
	void SetRect(CRect rect) { m_rect = rect; }
};

//////////////////////////////////////////////////////////////////////////
// CKofMFCTabCtrl

class KOFPACKDLLEXPORT CKofMFCTabCtrl : public CMFCTabCtrl
{
	DECLARE_DYNCREATE(CKofMFCTabCtrl)

public:
	CKofMFCTabCtrl();
	virtual ~CKofMFCTabCtrl();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void AdjustTabs();

protected:
	BOOL m_bIsDlgControl2;     // Tab is created on the dialog
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
};


