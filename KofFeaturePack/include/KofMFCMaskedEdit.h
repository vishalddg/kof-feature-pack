#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCMaskedEdit

class KOFPACKDLLEXPORT CKofMFCMaskedEdit : public CMFCMaskedEdit
{
	DECLARE_DYNAMIC(CKofMFCMaskedEdit)

public:
	CKofMFCMaskedEdit();
	virtual ~CKofMFCMaskedEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


