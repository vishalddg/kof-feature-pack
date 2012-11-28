// ..\src\KofGroup.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofGroup.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofGroup

IMPLEMENT_DYNAMIC(CKofGroup, CButton)

CKofGroup::CKofGroup()
{

}

CKofGroup::~CKofGroup()
{
}

#ifndef WM_UPDATEUISTATE
#define	WM_UPDATEUISTATE 0x0128
#endif

BEGIN_MESSAGE_MAP(CKofGroup, CButton)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_ENABLE()
	ON_MESSAGE(WM_UPDATEUISTATE, OnUpdateUIState)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()

BOOL CKofGroup::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CKofGroup::OnPaint()
{
	if (!TRUE && !FALSE)
	{
		Default();
		return;
	}

	CPaintDC dc(this); // device context for painting

	CMemDC* pMemDC = NULL;
	CDC* pDC = &dc;

	if (FALSE)
	{
		pMemDC = new CMemDC (dc, this);
		pDC = &pMemDC->GetDC ();
		afxGlobalData.DrawParentBackground (this, pDC);
	}

	CRect rectClient;
	GetClientRect (rectClient);

	CString strName;
	GetWindowText (strName);

	CFont* pOldFont = (CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT);
	ASSERT(pOldFont != NULL);

	pDC->SetBkMode (TRANSPARENT);
	pDC->SetTextColor (afxGlobalData.clrBarText);

	CKofStyleHelper::GetInstance ()->OnDrawGroup (pDC, this, rectClient, strName);

	pDC->SelectObject (pOldFont);

	if (pMemDC != NULL)
	{
		delete pMemDC;
	}
}

void CKofGroup::OnEnable( BOOL bEnable )
{
	CButton::OnEnable(bEnable);

	if (GetParent () != NULL)
	{
		CRect rect;
		GetWindowRect (rect);

		GetParent ()->ScreenToClient (&rect);
		GetParent ()->RedrawWindow (rect);
	}
}

LRESULT CKofGroup::OnUpdateUIState( WPARAM, LPARAM )
{
	return 0;
}

LRESULT CKofGroup::OnSetText( WPARAM, LPARAM lp )
{
	LRESULT lr = Default ();

	if (GetParent () != NULL)
	{
		CRect rect;
		GetWindowRect (rect);

		GetParent ()->ScreenToClient (&rect);
		GetParent ()->RedrawWindow (rect);
	}

	return lr;
}
