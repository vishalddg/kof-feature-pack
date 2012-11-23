#pragma once
#include "KofPack.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCButton

class KOFPACKDLLEXPORT CKofMFCButton : public CMFCButton
{
	DECLARE_DYNCREATE(CKofMFCButton)

public:
	CKofMFCButton();
	virtual ~CKofMFCButton();

protected:
	COLORREF m_clrText;
	BOOL m_bIsLeftText;
	BOOL m_b3State;
	BOOL m_bIndeterminate;

protected:
	virtual void DoDrawItem(CDC* pDCPaint, CRect rectClient, UINT itemState);

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
};


