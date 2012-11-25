// ..\src\KofRichEditCtrl.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofRichEditCtrl.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofRichEditCtrl

IMPLEMENT_DYNAMIC(CKofRichEditCtrl, CRichEditCtrl)

CKofRichEditCtrl::CKofRichEditCtrl()
{

}

CKofRichEditCtrl::~CKofRichEditCtrl()
{
}

BEGIN_MESSAGE_MAP(CKofRichEditCtrl, CRichEditCtrl)
	ON_WM_NCPAINT()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CKofRichEditCtrl::OnNcPaint()
{
	const BOOL bHasScrollBars = ((GetStyle () & WS_VSCROLL) == WS_VSCROLL) || ((GetStyle () & WS_HSCROLL) == WS_HSCROLL);

	CWindowDC dc (this);
	CRect rectWindow;
	GetWindowRect (rectWindow);

	if ((!TRUE && !FALSE))
	{
		CRichEditCtrl::OnNcPaint ();
	}
	else
	{
		if (bHasScrollBars)
		{
			CRichEditCtrl::OnNcPaint ();
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

void CKofRichEditCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CKofStyleHelper::GetInstance()->OnEditContextMenu(pWnd, point);
}
