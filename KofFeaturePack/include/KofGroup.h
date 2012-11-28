#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofGroup

class KOFPACKDLLEXPORT CKofGroup : public CButton
{
	DECLARE_DYNAMIC(CKofGroup)

public:
	CKofGroup();
	virtual ~CKofGroup();

protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg LRESULT OnUpdateUIState(WPARAM, LPARAM);
	afx_msg LRESULT OnSetText(WPARAM, LPARAM lp);
	DECLARE_MESSAGE_MAP()
};


