// KofDialogEx.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofDialogEx.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofDialogEx

IMPLEMENT_DYNAMIC(CKofDialogEx, CDialogEx)

CKofDialogEx::CKofDialogEx()
:m_KImpl(*this)
{

}

CKofDialogEx::CKofDialogEx( UINT nIDTemplate, CWnd *pParent /*= NULL*/ )
:CDialogEx(nIDTemplate, pParent), m_KImpl(*this)
{

}

CKofDialogEx::CKofDialogEx( LPCTSTR lpszTemplateName, CWnd *pParentWnd /*= NULL*/ )
:CDialogEx(lpszTemplateName, pParentWnd), m_KImpl(*this)
{

}

CKofDialogEx::~CKofDialogEx()
{
}


BEGIN_MESSAGE_MAP(CKofDialogEx, CDialogEx)
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
END_MESSAGE_MAP()

void CKofDialogEx::OnNcPaint()
{
	if (!m_KImpl.OnNcPaint())
	{
		Default ();
	}
}

void CKofDialogEx::EnableVisualManagerStyle( BOOL bEnable /*= TRUE*/, BOOL bNCArea /*= FALSE*/, const CList<UINT,UINT>* plstNonSubclassedItems /*= NULL*/ )
{
	ASSERT_VALID (this);

	m_KImpl.EnableVisualManagerStyle (bEnable, bEnable && bNCArea, plstNonSubclassedItems);

	if (bEnable && bNCArea)
	{
		m_KImpl.OnChangeVisualManager ();
	}
}

void CKofDialogEx::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	m_KImpl.OnActivate(nState, pWndOther);
}

BOOL CKofDialogEx::OnNcActivate(BOOL bActive)
{
	BOOL bRes = (BOOL)DefWindowProc (WM_NCACTIVATE, bActive, 0L);
	if (bRes)
	{
		m_KImpl.OnNcActivate(bActive);
	}
	return bRes;
}

void CKofDialogEx::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	m_KImpl.OnNcMouseMove(nHitTest, point);
	CDialogEx::OnNcMouseMove(nHitTest, point);
}

LRESULT CKofDialogEx::OnNcHitTest(CPoint point)
{
	LRESULT nHit = m_KImpl.OnNcHitTest(point);
	if (nHit != HTNOWHERE)
	{
		return nHit;
	}

	return CDialogEx::OnNcHitTest(point);
}

void CKofDialogEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_KImpl.OnLButtonDown(point);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CKofDialogEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_KImpl.OnLButtonUp(point);
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CKofDialogEx::OnMouseMove(UINT nFlags, CPoint point)
{
	m_KImpl.OnMouseMove(point);
	CDialogEx::OnMouseMove(nFlags, point);
}

LRESULT CKofDialogEx::OnSetText( WPARAM, LPARAM )
{
	LRESULT	lRes = Default();

	if (lRes)
	{
		RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW);
	}

	return lRes;
}


BOOL CKofDialogEx::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_KImpl.m_bHasBorder = (GetStyle () & WS_BORDER) != 0;
	EnableVisualManagerStyle(TRUE, TRUE);
	return TRUE;  
}

void CKofDialogEx::OnSize(UINT nType, int cx, int cy)
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

void CKofDialogEx::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	if ((lpwndpos->flags & SWP_FRAMECHANGED) == SWP_FRAMECHANGED)
	{
		m_KImpl.OnWindowPosChanged (lpwndpos);
	}
	CDialogEx::OnWindowPosChanged(lpwndpos);
}

void CKofDialogEx::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	m_KImpl.OnGetMinMaxInfo(lpMMI);
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

int CKofDialogEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;


	return m_KImpl.OnCreate();
}

void CKofDialogEx::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if (!m_KImpl.OnNcCalcSize(bCalcValidRects, lpncsp))
	{
		CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
	}
}

BOOL CKofDialogEx::OnEraseBkgnd(CDC* pDC)
{
	if (m_brBkgr.GetSafeHandle() == NULL && m_hBkgrBitmap == NULL && FALSE)
	{
		return CDialog::OnEraseBkgnd(pDC);
	}

	ASSERT_VALID(pDC);

	CRect rectClient;
	GetClientRect(rectClient);

	if (m_BkgrLocation != BACKGR_TILE || m_hBkgrBitmap == NULL)
	{
		if (m_brBkgr.GetSafeHandle() != NULL)
		{
			pDC->FillRect(rectClient, &m_brBkgr);
		}
		else if (1)
		{
			if (!CKofStyleHelper::GetInstance()->OnFillDialog(pDC, this, rectClient))
			{
				CDialog::OnEraseBkgnd (pDC);
			}
		}
		else
		{
			CDialog::OnEraseBkgnd(pDC);
		}
	}

	if (m_hBkgrBitmap == NULL)
	{
		return TRUE;
	}

	ASSERT(m_sizeBkgrBitmap != CSize(0, 0));

	if (m_BkgrLocation != BACKGR_TILE)
	{
		CPoint ptImage = rectClient.TopLeft();

		switch (m_BkgrLocation)
		{
		case BACKGR_TOPLEFT:
			break;

		case BACKGR_TOPRIGHT:
			ptImage.x = rectClient.right - m_sizeBkgrBitmap.cx;
			break;

		case BACKGR_BOTTOMLEFT:
			ptImage.y = rectClient.bottom - m_sizeBkgrBitmap.cy;
			break;

		case BACKGR_BOTTOMRIGHT:
			ptImage.x = rectClient.right - m_sizeBkgrBitmap.cx;
			ptImage.y = rectClient.bottom - m_sizeBkgrBitmap.cy;
			break;
		}

		pDC->DrawState(ptImage, m_sizeBkgrBitmap, m_hBkgrBitmap, DSS_NORMAL);
	}
	else
	{
		// Tile background image:
		for (int x = rectClient.left; x < rectClient.Width(); x += m_sizeBkgrBitmap.cx)
		{
			for (int y = rectClient.top; y < rectClient.Height(); y += m_sizeBkgrBitmap.cy)
			{
				pDC->DrawState(CPoint(x, y), m_sizeBkgrBitmap, m_hBkgrBitmap, DSS_NORMAL);
			}
		}
	}

	return TRUE;
}

HBRUSH CKofDialogEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (m_brBkgr.GetSafeHandle () != NULL || m_hBkgrBitmap != NULL ||
		TRUE)
	{
		HBRUSH hbr = m_KImpl.OnCtlColor (pDC, pWnd, nCtlColor);
		if (hbr != NULL)
		{
			return hbr;
		}
	}	

	return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

LRESULT CKofDialogEx::OnChangeVisualManager( WPARAM, LPARAM )
{
	m_KImpl.OnChangeVisualManager();
	return 0;
}

BOOL CKofDialogEx::PreTranslateMessage(MSG* pMsg)
{
	BOOL bRes = CDialogEx::PreTranslateMessage(pMsg);
	if (FALSE == bRes)
	{
		return m_KImpl.PreTranslateMessage(pMsg);
	}
	return bRes;
}

void CKofDialogEx::OnDestroy()
{
	m_KImpl.OnDestroy();
	CDialogEx::OnDestroy();
}
