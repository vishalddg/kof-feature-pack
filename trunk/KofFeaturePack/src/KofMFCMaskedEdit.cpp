// ..\src\KofMFCMaskedEdit.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofMFCMaskedEdit.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCMaskedEdit

IMPLEMENT_DYNAMIC(CKofMFCMaskedEdit, CMFCMaskedEdit)

CKofMFCMaskedEdit::CKofMFCMaskedEdit()
{

}

CKofMFCMaskedEdit::~CKofMFCMaskedEdit()
{
}

BEGIN_MESSAGE_MAP(CKofMFCMaskedEdit, CMFCMaskedEdit)
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CKofMFCMaskedEdit::OnNcPaint()
{
	const BOOL bHasScrollBars = ((GetStyle () & WS_VSCROLL) == WS_VSCROLL) || ((GetStyle () & WS_HSCROLL) == WS_HSCROLL);

	CWindowDC dc (this);
	CRect rectWindow;
	GetWindowRect (rectWindow);

	if (/*bHasScrollBars ||*/ (!TRUE && !FALSE))
	{
		CMFCMaskedEdit::OnNcPaint ();
	}
	else
	{
		if (bHasScrollBars)
		{
			CMFCMaskedEdit::OnNcPaint ();
		}
		CRect rectBorder = rectWindow;
		rectBorder.bottom -= rectBorder.top;
		rectBorder.right -= rectBorder.left;
		rectBorder.left = rectBorder.top = 0;
		CKofStyleHelper::GetInstance()->OnDrawEditBorder(&dc, rectBorder, FALSE, FALSE, IsWindowEnabled());
		rectBorder.DeflateRect(1, 1);
		dc.Draw3dRect(rectBorder, afxGlobalData.clrWindow, afxGlobalData.clrWindow);
	}

	if (GetStyle () & WS_BORDER)
	{
		CMFCVisualManager::GetInstance()->OnDrawControlBorder (this);
	}
}

HBRUSH CKofMFCMaskedEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
	if ((GetStyle() & ES_READONLY) == ES_READONLY && TRUE)
	{
		CBrush& br = CKofStyleHelper::GetInstance ()->GetDlgBackBrush (GetParent());

		LOGBRUSH lbr;
		br.GetLogBrush(&lbr);

		pDC->SetBkColor(lbr.lbColor);
		pDC->SetTextColor (afxGlobalData.clrBarText);
		return (HBRUSH)br.GetSafeHandle();
	}

	return NULL;
}

void CKofMFCMaskedEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CKofStyleHelper::GetInstance()->OnEditContextMenu(pWnd, point);
}
