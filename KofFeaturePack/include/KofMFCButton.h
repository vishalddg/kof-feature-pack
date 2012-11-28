#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCButton

class KOFPACKDLLEXPORT CKofMFCButton : public CMFCButton
{
	DECLARE_DYNCREATE(CKofMFCButton)

public:
	CKofMFCButton();
	virtual ~CKofMFCButton();

	void GetTooltip(CString& strTooltip);
	BOOL IsDefaultButton() const { return  m_bDefaultButton; }

protected:
	COLORREF m_clrText;
	BOOL m_bIsLeftText;
	BOOL m_b3State;
	BOOL m_bIndeterminate;
	BOOL m_bDefaultButton;

protected:
	virtual void DoDrawItem(CDC* pDCPaint, CRect rectClient, UINT itemState);
	virtual void InitStyleEx(DWORD dwStyle);
	virtual void PreSubclassWindow();
	virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDrawFocusRect(CDC* pDC, const CRect& rectClient);

protected:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnGetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnSetCheck(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()

public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnPaint();
};


