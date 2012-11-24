#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofProgressCtrl

class KOFPACKDLLEXPORT CKofProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CKofProgressCtrl)

public:
	CKofProgressCtrl();
	virtual ~CKofProgressCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcPaint();
};


