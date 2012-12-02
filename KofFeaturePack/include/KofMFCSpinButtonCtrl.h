#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofSpinButtonCtrl

class KOFPACKDLLEXPORT CKofMFCSpinButtonCtrl : public CMFCSpinButtonCtrl
{
public:
	CKofMFCSpinButtonCtrl();
	virtual ~CKofMFCSpinButtonCtrl();

	virtual void OnDraw(CDC* pDC);
protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


