#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCColorButton

class KOFPACKDLLEXPORT CKofMFCColorButton : public CMFCColorButton
{
	DECLARE_DYNAMIC(CKofMFCColorButton)

public:
	CKofMFCColorButton();
	virtual ~CKofMFCColorButton();

protected:
	virtual void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
	virtual void OnDrawBorder(CDC* pDC, CRect& rectClient, UINT uiState);

protected:
	DECLARE_MESSAGE_MAP()
};


