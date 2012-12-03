// ..\src\KofProgressCtrl.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofProgressCtrl.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofProgressCtrl

IMPLEMENT_DYNAMIC(CKofProgressCtrl, CProgressCtrl)

CKofProgressCtrl::CKofProgressCtrl()
{

}

CKofProgressCtrl::~CKofProgressCtrl()
{
}

BEGIN_MESSAGE_MAP(CKofProgressCtrl, CProgressCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
END_MESSAGE_MAP()

BOOL CKofProgressCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CKofProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	//if (!CMFCVisualManager::GetInstance()->OnFillParentBarBackground (this, pDC))
	{
		afxGlobalData.DrawParentBackground (this, pDC);
	}

	CRect rect;
	GetClientRect (rect);

	CRect rectProgress = rect;
	rectProgress.DeflateRect (1, 1);

	int nMin = 0;
	int nMax = 0;
	GetRange (nMin, nMax);

	CRect rectChunk (0, 0, 0, 0);

	if (nMax > nMin)
	{
		rectChunk = rectProgress;
		rectChunk.right = rectChunk.left + 
			GetPos () * rectChunk.Width () / (nMax - nMin);

		rectChunk.DeflateRect (1, 1);
	}


	CMFCRibbonProgressBar dummy;
	CKofStyleHelper::GetInstance()->OnDrawRibbonProgressBar(
		pDC, &dummy, rectProgress, rectChunk, FALSE);
}

void CKofProgressCtrl::OnNcCalcSize(BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS* /*lpncsp*/)
{
}

void CKofProgressCtrl::OnNcPaint()
{
}
