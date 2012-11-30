#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCEdit

class KOFPACKDLLEXPORT CKofMFCEdit : public CMFCEditBrowseCtrl
{
public:
	CKofMFCEdit();
	virtual ~CKofMFCEdit();

	void SetNeedBorder(BOOL bIsNeedBorder){m_bIsNeedBorder = bIsNeedBorder;}
protected:
	BOOL m_bIsNeedBorder;
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnDrawBrowseButton(CDC* pDC, CRect rect, BOOL bIsButtonPressed, BOOL bIsButtonHot);
	afx_msg void OnNcPaint();
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


