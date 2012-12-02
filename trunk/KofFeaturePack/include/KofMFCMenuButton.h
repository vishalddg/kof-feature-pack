#pragma once
#include "KofPack.h"
#include "KofMFCButton.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCMenuButton

class KOFPACKDLLEXPORT CKofMFCMenuButton : public CKofMFCButton
{
	DECLARE_DYNAMIC(CKofMFCMenuButton)

public:
	CKofMFCMenuButton();
	virtual ~CKofMFCMenuButton();

	virtual CSize SizeToContent(BOOL bCalcOnly = FALSE);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
public:
	BOOL  m_bRightArrow;
	HMENU m_hMenu;
	int   m_nMenuResult;
	BOOL  m_bStayPressed;
	BOOL  m_bOSMenu;       // User standard Windows menu either than library
	BOOL  m_bDefaultClick; // Allow default (on button text/image) processing

protected:
	BOOL  m_bMenuIsActive;
	BOOL  m_bClickOnMenu;

	virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
	virtual void OnShowMenu();
protected:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
};


