#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofStatic

class KOFPACKDLLEXPORT CKofStatic : public CStatic
{
	DECLARE_DYNAMIC(CKofStatic)

public:
	CKofStatic();
	virtual ~CKofStatic();

	void SetTextColor(COLORREF clrText) { m_clrText = clrText; }

protected:
	COLORREF m_clrText;
	HFONT m_hFont;

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnPaint();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM lp);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};


