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
	DECLARE_MESSAGE_MAP()
};


