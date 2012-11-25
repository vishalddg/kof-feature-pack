#pragma once
#include "KofPack.h"
#include "KofMFCEdit.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCFontComboBox

class KOFPACKDLLEXPORT CKofMFCFontComboBox : public CMFCFontComboBox
{
public:
	CKofMFCFontComboBox();
	virtual ~CKofMFCFontComboBox();

	CKofMFCEdit m_edit;
protected:
	BOOL m_bIsDroppedDown;
	CRect m_rectBtn;
	BOOL m_bIsButtonHighlighted;
	BOOL m_bTracked;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnCbnCloseup();
	afx_msg BOOL OnCbnDropdown();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
};


