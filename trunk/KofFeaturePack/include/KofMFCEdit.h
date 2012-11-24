#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCEdit

class KOFPACKDLLEXPORT CKofMFCEdit : public CMFCEditBrowseCtrl
{
	DECLARE_DYNAMIC(CKofMFCEdit)

public:
	CKofMFCEdit();
	virtual ~CKofMFCEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDrawBrowseButton(CDC* pDC, CRect rect, BOOL bIsButtonPressed, BOOL bIsButtonHot);
	afx_msg void OnNcPaint();
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


