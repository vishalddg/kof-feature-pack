#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofRichEditCtrl

class KOFPACKDLLEXPORT CKofRichEditCtrl : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CKofRichEditCtrl)

public:
	CKofRichEditCtrl();
	virtual ~CKofRichEditCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNcPaint();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};


