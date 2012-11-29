#include "StdAfx.h"
#include "..\include\KofDlgImpl.h"
#include "..\include\KofDialogEx.h"
#include "..\include\KofStyleHelper.h"
#include "..\include\KofStatic.h"
#include "..\include\KofMFCButton.h"
#include "..\include\KofComboBox.h"
#include "..\include\KofMFCSpinButtonCtrl.h"
#include "..\include\KofMFCEdit.h"
#include "..\include\KofProgressCtrl.h"

CKofDlgImpl::CKofDlgImpl(CWnd& dlg)
:m_Dlg(dlg),
m_nHotSysButton(HTNOWHERE),
m_nHitSysButton(HTNOWHERE),
m_bWindowPosChanging(FALSE),
m_bIsWindowRgn(FALSE),
m_bVisualManagerNCArea (FALSE),
m_bHasBorder(FALSE)
{
	m_rectRedraw.SetRectEmpty();
	m_rectResizeBox.SetRectEmpty();
}

CKofDlgImpl::~CKofDlgImpl(void)
{
	while (!m_lstCaptionSysButtons.IsEmpty ())
	{
		delete m_lstCaptionSysButtons.RemoveHead ();
	}
}

BOOL CKofDlgImpl::OnNcPaint()
{
	if (!IsOwnerDrawCaption())
	{
		return FALSE;
	}

	return CMFCVisualManager::GetInstance()->OnNcPaint(&m_Dlg, m_lstCaptionSysButtons, m_rectRedraw);
}

void CKofDlgImpl::RedrawCaptionButton( CMFCCaptionButtonEx* pBtn )
{
	if (pBtn ==	NULL)
	{
		return;
	}

	ASSERT_VALID (pBtn);

	m_rectRedraw = pBtn->GetRect ();
	m_Dlg.SendMessage (WM_NCPAINT);
	m_rectRedraw.SetRectEmpty ();

	m_Dlg.UpdateWindow ();
}

void CKofDlgImpl::OnLButtonDown( CPoint /*point*/ )
{
	if (m_nHotSysButton == HTNOWHERE)
	{
		return;
	}

	CMFCCaptionButtonEx* pBtn = GetSysButton (m_nHotSysButton);
	if (pBtn != NULL)
	{
		m_nHitSysButton = m_nHotSysButton;
		pBtn->m_bPushed = TRUE;
		RedrawCaptionButton (pBtn);
	}
}

CMFCCaptionButtonEx* CKofDlgImpl::GetSysButton( UINT nHit )
{
	for (POSITION pos = m_lstCaptionSysButtons.GetHeadPosition (); pos != NULL;)
	{
		CMFCCaptionButtonEx* pButton = (CMFCCaptionButtonEx*)
			m_lstCaptionSysButtons.GetNext (pos);
		ASSERT_VALID (pButton);

		if (pButton->m_nHit == nHit)
		{
			return pButton;
		}
	}

	return NULL;
}

void CKofDlgImpl::UpdateCaption()
{
	if (!IsOwnerDrawCaption ())
	{
		return;
	}

	if (m_lstCaptionSysButtons.IsEmpty ())
	{
		//------------------------
		// Create caption buttons:
		//------------------------
		const DWORD dwStyle = m_Dlg.GetStyle ();
		HMENU hSysMenu = NULL;
		CMenu* pSysMenu = m_Dlg.GetSystemMenu (FALSE);

		if (pSysMenu != NULL && ::IsMenu (pSysMenu->m_hMenu))
		{
			hSysMenu = pSysMenu->GetSafeHmenu ();
			if (!::IsMenu (hSysMenu) || (m_Dlg.GetStyle () & WS_SYSMENU) == 0)
			{
				hSysMenu = NULL;
			}
		}

		if (hSysMenu != NULL)
		{
			m_lstCaptionSysButtons.AddTail (new CMFCCaptionButtonEx (AFX_HTCLOSE));

			if ((dwStyle & WS_MAXIMIZEBOX) == WS_MAXIMIZEBOX)
			{
				m_lstCaptionSysButtons.AddTail (new CMFCCaptionButtonEx (AFX_HTMAXBUTTON));
			}

			if ((dwStyle & WS_MINIMIZEBOX) == WS_MINIMIZEBOX)
			{
				m_lstCaptionSysButtons.AddTail (new CMFCCaptionButtonEx (AFX_HTMINBUTTON));
			}

			if ((dwStyle & DS_CONTEXTHELP) == DS_CONTEXTHELP)
			{
				if (!m_Dlg.IsKindOf (RUNTIME_CLASS (CPropertySheet)))
				{
					m_lstCaptionSysButtons.AddTail (new CMFCCaptionButtonEx (AFX_HTMINBUTTON + 1));
				}
			}
		}
	}

	CRect rectCaption = GetCaptionRect ();

	{
		CSize sizeButton = CMFCVisualManager::GetInstance()->GetNcBtnSize (FALSE);
		sizeButton.cy = min (sizeButton.cy, rectCaption.Height () - 2);

		int x = rectCaption.right - sizeButton.cx;
		int y = rectCaption.top + max (0, (rectCaption.Height () - sizeButton.cy) / 2);

		for (POSITION pos = m_lstCaptionSysButtons.GetHeadPosition (); pos != NULL;)
		{
			CMFCCaptionButtonEx* pButton = (CMFCCaptionButtonEx*)
				m_lstCaptionSysButtons.GetNext (pos);
			ASSERT_VALID (pButton);

			pButton->SetRect (CRect (CPoint (x, y), sizeButton));

			x -= sizeButton.cx;
		}
	}

	m_Dlg.RedrawWindow (NULL, NULL,
		RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
}

CRect CKofDlgImpl::GetCaptionRect()
{
	CSize szSystemBorder (::GetSystemMetrics (SM_CXSIZEFRAME), ::GetSystemMetrics (SM_CYSIZEFRAME));

	if (m_Dlg.IsIconic () || 
		(m_Dlg.GetStyle () & WS_MAXIMIZE) == WS_MAXIMIZE)
	{
		szSystemBorder = CSize (0, 0);
	}
	else if ((m_Dlg.GetStyle () & WS_THICKFRAME) == 0)
	{
		szSystemBorder = CSize (::GetSystemMetrics (SM_CXFIXEDFRAME), ::GetSystemMetrics (SM_CXFIXEDFRAME));
	}


	CRect rectWnd;
	m_Dlg.GetWindowRect (&rectWnd);

	m_Dlg.ScreenToClient (&rectWnd);

	int cyOffset = szSystemBorder.cy;
	if (!m_Dlg.IsIconic ())
	{
		cyOffset += GetCaptionHeight ();
	}

	rectWnd.OffsetRect (szSystemBorder.cx, cyOffset);

	CRect rectCaption (	rectWnd.left + szSystemBorder.cx, 
		rectWnd.top + szSystemBorder.cy, 
		rectWnd.right - szSystemBorder.cx, 
		rectWnd.top + szSystemBorder.cy + GetCaptionHeight ());

	if (m_Dlg.IsIconic ())
	{
		rectCaption.top += ::GetSystemMetrics (SM_CYSIZEFRAME);
		rectCaption.right -= ::GetSystemMetrics (SM_CXSIZEFRAME);
	}

	return rectCaption;
}

int CKofDlgImpl::GetCaptionHeight()
{
	if (m_Dlg.GetSafeHwnd () == NULL)
	{
		return 0;
	}

	if (m_Dlg.GetExStyle () & WS_EX_TOOLWINDOW)
	{
		return ::GetSystemMetrics (SM_CYSMCAPTION);
	}

	return ::GetSystemMetrics (SM_CYCAPTION);
}

void CKofDlgImpl::OnChangeVisualManager()
{
	if (m_Dlg.GetSafeHwnd () == NULL)
	{
		return;
	}

	CRect rectWindow;
	m_Dlg.GetWindowRect (rectWindow);

	BOOL bZoomed = m_Dlg.IsZoomed ();

	if (IsOwnerDrawCaption ())
	{
		BOOL bChangeBorder = FALSE;

		if ((m_Dlg.GetStyle () & WS_BORDER) == WS_BORDER && m_bHasBorder)
		{
			bChangeBorder = TRUE;
			m_bWindowPosChanging = TRUE;
			m_Dlg.ModifyStyle (WS_BORDER, 0, SWP_FRAMECHANGED);
			m_bWindowPosChanging = FALSE;
		}

		m_bIsWindowRgn = CMFCVisualManager::GetInstance()->OnSetWindowRegion (
			&m_Dlg, rectWindow.Size ());

		if (bZoomed && bChangeBorder)
		{
			m_Dlg.ShowWindow (SW_MINIMIZE);
			m_Dlg.ShowWindow (SW_MAXIMIZE);
		}
	}
	else
	{
		BOOL bChangeBorder = FALSE;

		if ((m_Dlg.GetStyle () & WS_BORDER) == 0 && m_bHasBorder)
		{
			bChangeBorder = TRUE;
			m_bWindowPosChanging = TRUE;
			m_Dlg.ModifyStyle (0, WS_BORDER, SWP_FRAMECHANGED);
			m_bWindowPosChanging = FALSE;
		}

		if (m_bIsWindowRgn)
		{
			m_bIsWindowRgn = FALSE;
			m_Dlg.SetWindowRgn (NULL, TRUE);
		}

		if (bZoomed && bChangeBorder)
		{
			NCCALCSIZE_PARAMS params;
			ZeroMemory(&params, sizeof (NCCALCSIZE_PARAMS));
			params.rgrc[0].left   = rectWindow.left;
			params.rgrc[0].top    = rectWindow.top;
			params.rgrc[0].right  = rectWindow.right;
			params.rgrc[0].bottom = rectWindow.bottom;

			m_Dlg.CalcWindowRect (&params.rgrc[0], CFrameWnd::adjustBorder);

			if ((m_Dlg.GetStyle () & WS_CAPTION) == WS_CAPTION)
			{
				params.rgrc[0].top += GetCaptionHeight ();
			}

			m_Dlg.SetWindowPos (NULL, params.rgrc[0].left, params.rgrc[0].top, 
				params.rgrc[0].right - params.rgrc[0].left, params.rgrc[0].bottom - params.rgrc[0].top,
				SWP_NOACTIVATE | SWP_NOZORDER);
		}
		else
		{
			m_Dlg.SetWindowPos (NULL, -1, -1, rectWindow.Width () + 1, rectWindow.Height () + 1,
				SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
			m_Dlg.SetWindowPos (NULL, -1, -1, rectWindow.Width (), rectWindow.Height (),
				SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
		}
	}

	UpdateCaption ();
	UpdateCaptionButtons();
}

void CKofDlgImpl::OnWindowPosChanged( WINDOWPOS FAR* lpwndpos )
{
	if (m_bWindowPosChanging)
	{
		return;
	}

	if (((lpwndpos->flags & SWP_NOSIZE) == 0 || (lpwndpos->flags & SWP_FRAMECHANGED)) && 
		(IsOwnerDrawCaption ()))
	{
		m_bWindowPosChanging = TRUE;

		m_bIsWindowRgn = CMFCVisualManager::GetInstance()->OnSetWindowRegion (
			&m_Dlg, CSize (lpwndpos->cx, lpwndpos->cy));

		m_bWindowPosChanging = FALSE;
	}
}

void CKofDlgImpl::UpdateCaptionButtons()
{
	if ((m_Dlg.GetStyle () & WS_SYSMENU) == 0)
	{
		return;
	}

	CMenu* pSysMenu = m_Dlg.GetSystemMenu (FALSE);

	if (pSysMenu == NULL || !::IsMenu (pSysMenu->m_hMenu))
	{
		return;
	}

	for (POSITION pos = m_lstCaptionSysButtons.GetHeadPosition (); pos != NULL;)
	{
		CMFCCaptionButtonEx* pButton = (CMFCCaptionButtonEx*)m_lstCaptionSysButtons.GetNext (pos);
		ASSERT_VALID (pButton);

		if (pButton->GetHit () == AFX_HTCLOSE)
		{
			BOOL bGrayed = pSysMenu->GetMenuState (SC_CLOSE, MF_BYCOMMAND) & MF_GRAYED;
			pButton->m_bEnabled = bGrayed ? FALSE : TRUE;
		}

		if (pButton->GetHit () == AFX_HTMAXBUTTON)
		{
			BOOL bGrayed = pSysMenu->GetMenuState (SC_MAXIMIZE, MF_BYCOMMAND) & MF_GRAYED;
			pButton->m_bEnabled = bGrayed ? FALSE : TRUE;
		}

		if (pButton->GetHit () == AFX_HTMINBUTTON)
		{
			BOOL bGrayed = pSysMenu->GetMenuState (SC_MINIMIZE, MF_BYCOMMAND) & MF_GRAYED;
			pButton->m_bEnabled = bGrayed ? FALSE : TRUE;
		}
	}


	m_Dlg.RedrawWindow (NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
}

void CKofDlgImpl::EnableVisualManagerStyle( BOOL bEnable, BOOL bNCArea /*= FALSE*/, const CList<UINT,UINT>* plstNonSubclassedItems /*= NULL*/ )
{
	bEnable;
	m_bVisualManagerNCArea = bNCArea;
	plstNonSubclassedItems;

	if (m_Dlg.GetSafeHwnd () == NULL)
	{
		return;
	}

	CWnd* pWndChild = m_Dlg.GetWindow (GW_CHILD);

	while (pWndChild != NULL)
	{
		ASSERT_VALID (pWndChild);

		if (plstNonSubclassedItems != NULL && plstNonSubclassedItems->Find (pWndChild->GetDlgCtrlID ()) != NULL)
		{
			pWndChild = pWndChild->GetNextWindow ();
			continue;
		}

		if (bEnable &&
			CWnd::FromHandlePermanent (pWndChild->GetSafeHwnd ()) == NULL)
		{
#define MAX_CLASS_NAME		255
#define STATIC_CLASS		_T("Static")
#define BUTTON_CLASS		_T("Button")
#define EDIT_CLASS			_T("Edit")
#define	COMBOBOX_CLASS		_T("ComboBox")
#define SCROLLBAR_CLASS		_T("ScrollBar")

			TCHAR lpszClassName [MAX_CLASS_NAME + 1];

			::GetClassName (pWndChild->GetSafeHwnd (), lpszClassName, MAX_CLASS_NAME);
			CString strClass = lpszClassName;

			CWnd* pWndSubclassedCtrl = NULL;

			if (strClass == STATIC_CLASS)
			{
				pWndSubclassedCtrl = new CKofStatic;
			}
			else if (strClass == BUTTON_CLASS)
			{
				if ((pWndChild->GetStyle () & 0xF) == BS_GROUPBOX)
				{
					pWndSubclassedCtrl = new CKofGroup;
				}
				else
				{
					pWndSubclassedCtrl = new CKofMFCButton;
				}
			}
			else if (strClass == PROGRESS_CLASS)
			{
				pWndSubclassedCtrl = new CKofProgressCtrl;
			}
			else if (strClass == TRACKBAR_CLASS)
			{
				//pWndSubclassedCtrl = new CBCGPSliderCtrl;
			}
			else if (strClass == EDIT_CLASS)
			{
				pWndSubclassedCtrl = new CKofMFCEdit;
			}
			else if (strClass == COMBOBOX_CLASS)
			{
				pWndSubclassedCtrl = new CKofComboBox;
			}
			else if (strClass == SCROLLBAR_CLASS)
			{
				//pWndSubclassedCtrl = new CBCGPScrollBar;
			}
			else if (strClass == UPDOWN_CLASS)
			{
				pWndSubclassedCtrl = new CKofMFCSpinButtonCtrl;
			}

			if (pWndSubclassedCtrl != NULL)
			{
				m_arSubclassedCtrls.Add (pWndSubclassedCtrl);
				pWndSubclassedCtrl->SubclassWindow (pWndChild->GetSafeHwnd ());
			}
		}
		pWndChild = pWndChild->GetNextWindow ();
	}
	OnChangeVisualManager ();

	if (m_Dlg.IsWindowVisible ())
	{
		m_Dlg.RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE | RDW_ALLCHILDREN);
	}
}

void CKofDlgImpl::OnNcActivate( BOOL& bActive )
{
	//----------------------------------------
	// Stay active if WF_STAYACTIVE bit is on:
	//----------------------------------------
	if (m_Dlg.m_nFlags & WF_STAYACTIVE)
	{
		bActive = TRUE;
	}

	//--------------------------------------------------
	// But do not stay active if the window is disabled:
	//--------------------------------------------------
	if (!m_Dlg.IsWindowEnabled ())
	{
		bActive = FALSE;
	}

	if (IsOwnerDrawCaption ())
	{
		CMFCVisualManager::GetInstance()->OnNcActivate(&m_Dlg, bActive);
		m_Dlg.RedrawWindow (CRect (0, 0, 0, 0), NULL,
			RDW_FRAME | RDW_INVALIDATE | RDW_UPDATENOW | RDW_NOCHILDREN);
	}
}

void CKofDlgImpl::OnActivate( UINT nState, CWnd* pWndOther )
{
	pWndOther;
	if (nState == WA_INACTIVE && IsOwnerDrawCaption ())
	{
		m_Dlg.RedrawWindow(NULL, NULL, RDW_FRAME | RDW_UPDATENOW);
	} 
}

void CKofDlgImpl::OnNcMouseMove( UINT nHitTest, CPoint point )
{
	nHitTest;
	if (!IsOwnerDrawCaption())
	{
		return;
	}

	OnTrackCaptionButtons(point);
}

void CKofDlgImpl::OnTrackCaptionButtons( CPoint point )
{
	if (CMFCPopupMenu::GetActiveMenu () != NULL)
	{
		return;
	}

	UINT nHot = m_nHotSysButton;
	CMFCCaptionButtonEx* pBtn = GetSysButton (OnNcHitTest (point));

	if (pBtn != NULL && pBtn->m_bEnabled)
	{
		m_nHotSysButton = pBtn->GetHit ();
		pBtn->m_bFocused = TRUE;
	}
	else
	{
		m_nHotSysButton = HTNOWHERE;
	}

	if (m_nHotSysButton != nHot)
	{
		RedrawCaptionButton (pBtn);

		CMFCCaptionButtonEx* pBtnOld = GetSysButton (nHot);
		if (pBtnOld != NULL)
		{
			pBtnOld->m_bFocused = FALSE;
			RedrawCaptionButton (pBtnOld);
		}
	}

	if (m_nHitSysButton == HTNOWHERE)
	{
		if (nHot != HTNOWHERE && m_nHotSysButton == HTNOWHERE)
		{
			::ReleaseCapture();
		}
		else if (nHot == HTNOWHERE && m_nHotSysButton != HTNOWHERE)
		{
			m_Dlg.SetCapture ();
		}
	}
}

UINT CKofDlgImpl::OnNcHitTest( CPoint point )
{
	m_Dlg.ScreenToClient (&point);

	if (!m_rectResizeBox.IsRectEmpty ())
	{
		if (m_rectResizeBox.PtInRect(point))
		{
			BOOL bRTL = m_Dlg.GetExStyle() & WS_EX_LAYOUTRTL;
			return bRTL ? HTBOTTOMLEFT : HTBOTTOMRIGHT;
		}
	}

	if (!IsOwnerDrawCaption ())
	{
		return HTNOWHERE;
	}

	const CSize szSystemBorder(::GetSystemMetrics (SM_CXSIZEFRAME), ::GetSystemMetrics (SM_CYSIZEFRAME));

	int cxOffset = szSystemBorder.cx;
	int cyOffset = szSystemBorder.cy;
	if (!m_Dlg.IsIconic ())
	{
		cyOffset += GetCaptionHeight ();
	}

	if (m_Dlg.IsZoomed ())
	{
		cxOffset -= szSystemBorder.cx;
		cyOffset -= szSystemBorder.cy;
	}

	point.Offset (cxOffset, cyOffset);

	for (POSITION pos = m_lstCaptionSysButtons.GetHeadPosition (); pos != NULL;)
	{
		CMFCCaptionButtonEx* pButton = (CMFCCaptionButtonEx*)
			m_lstCaptionSysButtons.GetNext (pos);
		ASSERT_VALID (pButton);

		if (pButton->GetRect ().PtInRect (point))
		{
			return pButton->m_nHit;
		}
	}

	CRect rectCaption = GetCaptionRect ();
	if (rectCaption.PtInRect (point))
	{
		if ((m_Dlg.GetExStyle () & WS_EX_TOOLWINDOW) == 0)
		{
			CRect rectSysMenu = rectCaption;
			rectSysMenu.right = rectSysMenu.left + ::GetSystemMetrics (SM_CXSMICON) + 2 +
				(m_Dlg.IsZoomed () ? szSystemBorder.cx : 0);

			return rectSysMenu.PtInRect (point) ? HTSYSMENU : HTCAPTION;
		}

		return HTCAPTION;
	}

	return HTNOWHERE;
}

void CKofDlgImpl::OnLButtonUp( CPoint /*point*/ )
{
	if (!IsOwnerDrawCaption ())
	{
		return;
	}

	switch (m_nHitSysButton)
	{
	case AFX_HTCLOSE:
	case AFX_HTMAXBUTTON:
	case AFX_HTMINBUTTON:
	case AFX_HTMINBUTTON + 1:
		{
			UINT nHot = m_nHotSysButton;
			UINT nHit = m_nHitSysButton;

			StopCaptionButtonsTracking ();

			if (nHot == nHit)
			{
				UINT nSysCmd = 0;

				switch (nHot)
				{
				case AFX_HTCLOSE:
					nSysCmd = SC_CLOSE;
					break;

				case AFX_HTMAXBUTTON:
					nSysCmd = 
						(m_Dlg.GetStyle () & WS_MAXIMIZE) == WS_MAXIMIZE ? SC_RESTORE : SC_MAXIMIZE;
					break;

				case AFX_HTMINBUTTON:
					nSysCmd = m_Dlg.IsIconic () ? SC_RESTORE : SC_MINIMIZE;
					break;

				case AFX_HTMINBUTTON + 1:
					nSysCmd = SC_CONTEXTHELP;
					break;
				}

				m_Dlg.PostMessage (WM_SYSCOMMAND, nSysCmd);
			}
		}
	}
}

void CKofDlgImpl::StopCaptionButtonsTracking()
{
	if (m_nHitSysButton != HTNOWHERE)
	{
		CMFCCaptionButtonEx* pBtn = GetSysButton (m_nHitSysButton);
		m_nHitSysButton = HTNOWHERE;

		ReleaseCapture ();
		if (pBtn != NULL)
		{
			pBtn->m_bPushed = FALSE;
			RedrawCaptionButton (pBtn);
		}
	}

	if (m_nHotSysButton != HTNOWHERE)
	{
		CMFCCaptionButtonEx* pBtn = GetSysButton (m_nHotSysButton);
		m_nHotSysButton = HTNOWHERE;

		ReleaseCapture ();
		if (pBtn != NULL)
		{
			pBtn->m_bFocused = FALSE;
			RedrawCaptionButton (pBtn);
		}
	}
}

void CKofDlgImpl::OnMouseMove( CPoint point )
{
	if (!IsOwnerDrawCaption ())
	{
		return;
	}

	CPoint ptScreen = point;
	m_Dlg.ClientToScreen (&ptScreen);

	OnTrackCaptionButtons (ptScreen);
}

void CKofDlgImpl::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI )
{
	ASSERT (lpMMI != NULL);

	if ((m_Dlg.GetStyle () & WS_CAPTION) == 0 ||
		(m_Dlg.GetStyle () & WS_BORDER) == 0)
	{
		CRect rectWindow;
		m_Dlg.GetWindowRect (&rectWindow);

		if (m_Dlg.IsIconic ())
		{
			WINDOWPLACEMENT wp;
			wp.length = sizeof (WINDOWPLACEMENT);

			m_Dlg.GetWindowPlacement (&wp);

			rectWindow = wp.rcNormalPosition;
		}

		CRect rect (0, 0, 0, 0);

		MONITORINFO mi;
		mi.cbSize = sizeof (MONITORINFO);

		if (GetMonitorInfo (MonitorFromPoint (rectWindow.CenterPoint (), MONITOR_DEFAULTTONEAREST),
			&mi))
		{
			CRect rectWork = mi.rcWork;
			CRect rectScreen = mi.rcMonitor;

			rect.left = rectWork.left - rectScreen.left;
			rect.top = rectWork.top - rectScreen.top;

			rect.right = rect.left + rectWork.Width ();
			rect.bottom = rect.top + rectWork.Height ();
		}
		else
		{
			::SystemParametersInfo (SPI_GETWORKAREA, 0, &rect, 0);
		}

		int nShellAutohideBars = afxGlobalData.m_nShellAutohideBars;

		if (nShellAutohideBars & AFX_AUTOHIDE_BOTTOM)
		{
			rect.bottom -= 2;
		}

		if (nShellAutohideBars & AFX_AUTOHIDE_TOP)
		{
			rect.top += 2;
		}

		if (nShellAutohideBars & AFX_AUTOHIDE_RIGHT)
		{
			rect.right -= 2;
		}

		if (nShellAutohideBars & AFX_AUTOHIDE_LEFT)
		{
			rect.left += 2;
		}

		lpMMI->ptMaxPosition.x = rect.left;
		lpMMI->ptMaxPosition.y = rect.top;
		lpMMI->ptMaxSize.x = rect.Width ();
		lpMMI->ptMaxSize.y = rect.Height ();
	}
}

int CKofDlgImpl::OnCreate()
{
	return 0;
}

BOOL CKofDlgImpl::OnNcCalcSize( BOOL /*bCalcValidRects*/, NCCALCSIZE_PARAMS FAR* lpncsp )
{
	ASSERT (lpncsp != NULL);

	if ((m_Dlg.GetStyle () & WS_CAPTION) == 0)
	{
		m_bVisualManagerNCArea = FALSE;
	}

	if (IsOwnerDrawCaption ())
	{
		lpncsp->rgrc[0].top += GetCaptionHeight ();
	}

	return (m_Dlg.GetStyle () & WS_MAXIMIZE) == WS_MAXIMIZE && IsOwnerDrawCaption ();
}

HBRUSH CKofDlgImpl::OnCtlColor( CDC* pDC, CWnd* pWnd, UINT nCtlColor )
{
#define MAX_CLASS_NAME	255
#define STATIC_CLASS	_T("Static")
#define BUTTON_CLASS	_T("Button")

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		TCHAR lpszClassName [MAX_CLASS_NAME + 1];

		::GetClassName (pWnd->GetSafeHwnd (), lpszClassName, MAX_CLASS_NAME);
		CString strClass = lpszClassName;

		if (strClass == STATIC_CLASS)
		{
			pDC->SetBkMode(TRANSPARENT);

			if (TRUE)
			{
				pDC->SetTextColor (afxGlobalData.clrBarText);
			}

			if (TRUE && (pWnd->GetStyle () & SS_ICON) != SS_ICON)
			{
				return (HBRUSH) ::GetStockObject (HOLLOW_BRUSH);
			}

			if (FALSE)
			{
				return (HBRUSH) ::GetStockObject (WHITE_BRUSH);
			}

			return (HBRUSH) CKofStyleHelper::GetInstance()->GetDlgBackBrush (&m_Dlg).GetSafeHandle ();
		}

		if (strClass == BUTTON_CLASS)
		{
			DWORD dwStyle = pWnd->GetStyle ();

			if (dwStyle & BS_GROUPBOX)
			{
				if (TRUE)
				{
					pDC->SetTextColor (afxGlobalData.clrBarText);
					pDC->SetBkMode(TRANSPARENT);
					return (HBRUSH) CKofStyleHelper::GetInstance()->GetDlgBackBrush (&m_Dlg).GetSafeHandle ();
				}
			}

			if ((dwStyle & BS_CHECKBOX) == 0)
			{
				pDC->SetBkMode(TRANSPARENT);
			}

			return (HBRUSH) ::GetStockObject (FALSE ? WHITE_BRUSH : HOLLOW_BRUSH);
		}
	}

	return NULL;
}

BOOL CKofDlgImpl::PreTranslateMessage( MSG* pMsg )
{
	switch (pMsg->message)
	{
		case WM_NCRBUTTONUP:
			if (pMsg->message == WM_NCRBUTTONUP && pMsg->hwnd == m_Dlg.GetSafeHwnd () && IsOwnerDrawCaption ())
			{
				CPoint pt (AFX_GET_X_LPARAM(pMsg->lParam), AFX_GET_Y_LPARAM(pMsg->lParam));

				UINT nHit = OnNcHitTest (pt);

				if (nHit == HTCAPTION || nHit == HTSYSMENU)
				{
					CMenu* pMenu = m_Dlg.GetSystemMenu (FALSE);
					if (pMenu->GetSafeHmenu () != NULL && ::IsMenu (pMenu->GetSafeHmenu ()))
					{
						/*UINT uiRes = ::TrackPopupMenu (pMenu->GetSafeHmenu(), TPM_LEFTBUTTON | TPM_RETURNCMD, 
							pt.x, pt.y, 0, m_Dlg.GetSafeHwnd (), NULL);*/

						UINT uiRes = 0;
						if (((CWinAppEx*)AfxGetApp())->GetContextMenuManager() != NULL)
						{
							((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(pMenu->GetSafeHmenu(), pt.x, pt.y, &m_Dlg, TRUE);
						} 
						else
						{
							uiRes = ::TrackPopupMenu (pMenu->GetSafeHmenu(), TPM_LEFTBUTTON | TPM_RETURNCMD, 
								pt.x, pt.y, 0, m_Dlg.GetSafeHwnd (), NULL);
						}

						if (uiRes != 0)
						{
							m_Dlg.SendMessage (WM_SYSCOMMAND, uiRes);
							return TRUE;
						}
					}

				}
			}
			break;
	}

	return FALSE;
}

void CKofDlgImpl::OnDestroy()
{
	for (int i = 0; i < m_arSubclassedCtrls.GetSize(); i++)
	{
		delete m_arSubclassedCtrls [i];
	}

	m_arSubclassedCtrls.RemoveAll();
}
