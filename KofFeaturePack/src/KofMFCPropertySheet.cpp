// ..\src\KofMFCPropertySheet.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofMFCPropertySheet.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCPropertySheet

IMPLEMENT_DYNAMIC(CKofMFCPropertySheet, CMFCPropertySheet)

CKofMFCPropertySheet::CKofMFCPropertySheet()
:m_KImpl(*this)
{
}

CKofMFCPropertySheet::CKofMFCPropertySheet( UINT nIDCaption, CWnd* pParentWnd /*= NULL*/, UINT iSelectPage /*= 0*/ )
:CMFCPropertySheet(nIDCaption, pParentWnd, iSelectPage),
m_KImpl(*this)
{
}

CKofMFCPropertySheet::CKofMFCPropertySheet( LPCTSTR pszCaption, CWnd* pParentWnd /*= NULL*/, UINT iSelectPage /*= 0*/ )
:CMFCPropertySheet(pszCaption, pParentWnd, iSelectPage),
m_KImpl(*this)
{
}

CKofMFCPropertySheet::~CKofMFCPropertySheet()
{
}

BEGIN_MESSAGE_MAP(CKofMFCPropertySheet, CMFCPropertySheet)
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_NCMOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_NCCALCSIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_ERASEBKGND()
	ON_WM_GETMINMAXINFO()
	ON_WM_CTLCOLOR()
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGEVISUALMANAGER, OnChangeVisualManager)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CKofMFCPropertySheet::OnSize(UINT nType, int cx, int cy)
{
	if (m_KImpl.IsOwnerDrawCaption())
	{
		CRect rectWindow;
		GetWindowRect (rectWindow);

		WINDOWPOS wndpos;
		wndpos.flags = SWP_FRAMECHANGED;
		wndpos.x     = rectWindow.left;
		wndpos.y     = rectWindow.top;
		wndpos.cx    = rectWindow.Width();
		wndpos.cy    = rectWindow.Height();

		m_KImpl.OnWindowPosChanged(&wndpos);
	}

	m_KImpl.UpdateCaption();
	CPropertySheet::OnSize(nType, cx, cy);
}

void CKofMFCPropertySheet::OnNcPaint()
{
	if (!m_KImpl.OnNcPaint())
	{
		Default();
	}
}

void CKofMFCPropertySheet::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	m_KImpl.OnNcMouseMove(nHitTest, point);
	CMFCPropertySheet::OnNcMouseMove(nHitTest, point);
}

void CKofMFCPropertySheet::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_KImpl.OnLButtonUp(point);
	CMFCPropertySheet::OnLButtonUp(nFlags, point);
}

void CKofMFCPropertySheet::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_KImpl.OnLButtonDown(point);
	CMFCPropertySheet::OnLButtonDown(nFlags, point);
}

LRESULT CKofMFCPropertySheet::OnNcHitTest(CPoint point)
{
	LRESULT nHit = m_KImpl.OnNcHitTest(point);
	if (nHit != HTNOWHERE)
	{
		return nHit;
	}

	return CMFCPropertySheet::OnNcHitTest(point);
}

void CKofMFCPropertySheet::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if (!m_KImpl.OnNcCalcSize(bCalcValidRects, lpncsp))
	{
		CMFCPropertySheet::OnNcCalcSize(bCalcValidRects, lpncsp);
	}
}

void CKofMFCPropertySheet::OnMouseMove(UINT nFlags, CPoint point)
{
	m_KImpl.OnMouseMove(point);
	CMFCPropertySheet::OnMouseMove(nFlags, point);
}

void CKofMFCPropertySheet::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	if ((lpwndpos->flags & SWP_FRAMECHANGED) == SWP_FRAMECHANGED)
	{
		m_KImpl.OnWindowPosChanged (lpwndpos);
	}
	CMFCPropertySheet::OnWindowPosChanged(lpwndpos);
}

BOOL CKofMFCPropertySheet::OnEraseBkgnd(CDC* pDC)
{
	CRect rectClient;
	GetClientRect (rectClient);
	if (!TRUE || !CKofStyleHelper::GetInstance ()->OnFillDialog (pDC, this, rectClient))
	{
		BOOL bRes = CPropertySheet::OnEraseBkgnd(pDC);
		return bRes;
	}

	/*if (m_bDrawPageFrame)
	{
		CWnd* pPage = GetActivePage ();
		if (pPage->GetSafeHwnd () != NULL)
		{
			CRect rectFrame;
			pPage->GetWindowRect (rectFrame);
			ScreenToClient (&rectFrame);

			CPenSelector pen (*pDC, globalData.clrBarShadow);

			pDC->MoveTo (rectClient.left, rectFrame.bottom + 1);
			pDC->LineTo (rectClient.right, rectFrame.bottom + 1);
		}

		if (m_look == PropSheetLook_Tree && m_wndTree.GetSafeHwnd () != NULL)
		{
			CRect rectTree;
			m_wndTree.GetWindowRect (rectTree);
			ScreenToClient (&rectTree);

			rectTree.InflateRect (1, 1);

			pDC->Draw3dRect (rectTree, globalData.clrBarShadow, globalData.clrBarShadow);
		}
	}*/

	return TRUE;
}

void CKofMFCPropertySheet::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	m_KImpl.OnGetMinMaxInfo(lpMMI);
	CMFCPropertySheet::OnGetMinMaxInfo(lpMMI);
}

HBRUSH CKofMFCPropertySheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (FALSE)
	{
		HBRUSH hbr = m_KImpl.OnCtlColor (pDC, pWnd, nCtlColor);
		if (hbr != NULL)
		{
			return hbr;
		}
	}	
	HBRUSH hbr = CMFCPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

LRESULT CKofMFCPropertySheet::OnChangeVisualManager( WPARAM, LPARAM )
{
	m_KImpl.OnChangeVisualManager();
	return 0;
}

LRESULT CKofMFCPropertySheet::OnSetText( WPARAM, LPARAM )
{
	LRESULT	lRes = Default();

	if (lRes)
	{
		RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	}

	return lRes;
}

BOOL CKofMFCPropertySheet::OnInitDialog()
{
	BOOL bResult = CMFCPropertySheet::OnInitDialog();

	m_KImpl.m_bHasBorder = (GetStyle () & WS_BORDER) != 0;
	EnableVisualManagerStyle(TRUE, TRUE);
	return bResult;
}

void CKofMFCPropertySheet::EnableVisualManagerStyle( BOOL bEnable /*= TRUE*/, BOOL bNCArea /*= FALSE*/, const CList<UINT,UINT>* plstNonSubclassedItems /*= NULL*/ )
{
	ASSERT_VALID (this);

	m_KImpl.EnableVisualManagerStyle (bEnable, bEnable && bNCArea, plstNonSubclassedItems);

	if (bEnable && bNCArea)
	{
		m_KImpl.OnChangeVisualManager ();
	}
}

BOOL CKofMFCPropertySheet::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRes = CMFCPropertySheet::PreTranslateMessage(pMsg);
	if (FALSE == bRes)
	{
		return m_KImpl.PreTranslateMessage(pMsg);
	}
	return bRes;
}

void CKofMFCPropertySheet::OnDestroy()
{
	m_KImpl.OnDestroy();
	CMFCPropertySheet::OnDestroy();
}
