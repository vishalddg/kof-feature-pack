// ..\src\KofFileDialog.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofFileDialog.h"

#define WM_INITVISUAL (WM_APP + 1)
//////////////////////////////////////////////////////////////////////////
// CKofFileDialog

IMPLEMENT_DYNAMIC(CKofFileDialog, CFileDialog)

CKofFileDialog::CKofFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd, 0, FALSE)
		,m_KImpl(*this)
{

}

CKofFileDialog::~CKofFileDialog()
{
}

BEGIN_MESSAGE_MAP(CKofFileDialog, CFileDialog)
	ON_WM_NCPAINT()
	ON_WM_ACTIVATE()
	ON_WM_NCACTIVATE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_WM_SIZE()
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_GETMINMAXINFO()
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGEVISUALMANAGER, OnChangeVisualManager)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_INITVISUAL, OnPostInit)
END_MESSAGE_MAP()

void CKofFileDialog::OnNcPaint()
{
	if (!m_KImpl.OnNcPaint())
	{
		Default ();
	}
}

void CKofFileDialog::EnableVisualManagerStyle( BOOL bEnable /*= TRUE*/, BOOL bNCArea /*= FALSE*/, const CList<UINT,UINT>* plstNonSubclassedItems /*= NULL*/ )
{
	ASSERT_VALID (this);
	CWnd* pshell = GetParent()->GetDlgItem(lst2);
	if (pshell) {
		TRACE(_T("hwnd=\n"));
		//pshell->SendMessage(WM_COMMAND, cmd);
		//return TRUE;
	}
	m_KImpl.EnableVisualManagerStyle (bEnable, bEnable && bNCArea, plstNonSubclassedItems);

	if (bEnable && bNCArea)
	{
		m_KImpl.OnChangeVisualManager ();
	}
}

void CKofFileDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CFileDialog::OnActivate(nState, pWndOther, bMinimized);
	m_KImpl.OnActivate(nState, pWndOther);
}

BOOL CKofFileDialog::OnNcActivate(BOOL bActive)
{
	BOOL bRes = (BOOL)DefWindowProc (WM_NCACTIVATE, bActive, 0L);
	if (bRes)
	{
		m_KImpl.OnNcActivate(bActive);
	}
	return bRes;
}

void CKofFileDialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	m_KImpl.OnNcMouseMove(nHitTest, point);
	CFileDialog::OnNcMouseMove(nHitTest, point);
}

LRESULT CKofFileDialog::OnNcHitTest(CPoint point)
{
	LRESULT nHit = m_KImpl.OnNcHitTest(point);
	if (nHit != HTNOWHERE)
	{
		return nHit;
	}

	return CFileDialog::OnNcHitTest(point);
}

void CKofFileDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_KImpl.OnLButtonDown(point);
	CFileDialog::OnLButtonDown(nFlags, point);
}

void CKofFileDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_KImpl.OnLButtonUp(point);
	CFileDialog::OnLButtonUp(nFlags, point);
}

void CKofFileDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	m_KImpl.OnMouseMove(point);
	CFileDialog::OnMouseMove(nFlags, point);
}

LRESULT CKofFileDialog::OnSetText( WPARAM, LPARAM )
{
	LRESULT	lRes = Default();

	if (lRes)
	{
		RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	}

	return lRes;
}


BOOL CKofFileDialog::OnInitDialog()
{
	CFileDialog::OnInitDialog();
	PostMessage(WM_INITVISUAL,0,0);
	m_KImpl.m_bHasBorder = (GetStyle () & WS_BORDER) != 0;
	return TRUE;  
}

void CKofFileDialog::OnSize(UINT nType, int cx, int cy)
{
	if (m_KImpl.IsOwnerDrawCaption ())
	{
		CRect rectWindow;
		GetWindowRect (rectWindow);

		WINDOWPOS wndpos;
		wndpos.flags = SWP_FRAMECHANGED;
		wndpos.x     = rectWindow.left;
		wndpos.y     = rectWindow.top;
		wndpos.cx    = rectWindow.Width ();
		wndpos.cy    = rectWindow.Height ();

		m_KImpl.OnWindowPosChanged (&wndpos);
	}

	m_KImpl.UpdateCaption ();


	CDialog::OnSize(nType, cx, cy);
}

void CKofFileDialog::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	if ((lpwndpos->flags & SWP_FRAMECHANGED) == SWP_FRAMECHANGED)
	{
		m_KImpl.OnWindowPosChanged (lpwndpos);
	}
	CFileDialog::OnWindowPosChanged(lpwndpos);
}

void CKofFileDialog::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	m_KImpl.OnGetMinMaxInfo(lpMMI);
	CFileDialog::OnGetMinMaxInfo(lpMMI);
}

int CKofFileDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFileDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return m_KImpl.OnCreate();
}

void CKofFileDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if (!m_KImpl.OnNcCalcSize(bCalcValidRects, lpncsp))
	{
		CFileDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
	}
}

BOOL CKofFileDialog::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

HBRUSH CKofFileDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (TRUE)
	{
		HBRUSH hbr = m_KImpl.OnCtlColor (pDC, pWnd, nCtlColor);
		if (hbr != NULL)
		{
			return hbr;
		}
	}	

	return CFileDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

LRESULT CKofFileDialog::OnChangeVisualManager( WPARAM, LPARAM )
{
	m_KImpl.OnChangeVisualManager();
	return 0;
}

BOOL CKofFileDialog::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRes = CFileDialog::PreTranslateMessage(pMsg);
	if (FALSE == bRes)
	{
		return m_KImpl.PreTranslateMessage(pMsg);
	}
	return bRes;
}

void CKofFileDialog::OnDestroy()
{
	m_KImpl.OnDestroy();
	CFileDialog::OnDestroy();
}

LRESULT CKofFileDialog::OnPostInit( WPARAM wp, LPARAM lp )
{
	EnableVisualManagerStyle(TRUE, TRUE);
	return 0;
}