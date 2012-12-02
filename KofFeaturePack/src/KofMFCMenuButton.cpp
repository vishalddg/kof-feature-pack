// ..\src\KofMFCMenuButton.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofMFCMenuButton.h"

static const int nImageHorzMargin = 10;

//////////////////////////////////////////////////////////////////////////
// CKofMFCMenuButton

IMPLEMENT_DYNAMIC(CKofMFCMenuButton, CKofMFCButton)

CKofMFCMenuButton::CKofMFCMenuButton()
{
	m_bRightArrow = FALSE;
	m_hMenu = NULL;
	m_nMenuResult = 0;
	m_bMenuIsActive = FALSE;
	m_bStayPressed = FALSE;
	m_bOSMenu = TRUE;
	m_bDefaultClick = FALSE;
	m_bClickOnMenu = FALSE;
}

CKofMFCMenuButton::~CKofMFCMenuButton()
{
}

BEGIN_MESSAGE_MAP(CKofMFCMenuButton, CKofMFCButton)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

CSize CKofMFCMenuButton::SizeToContent(BOOL bCalcOnly)
{
	CSize size = CKofMFCButton::SizeToContent(FALSE);
	size.cx += CMenuImages::Size().cx;

	if (!bCalcOnly)
	{
		SetWindowPos(NULL, -1, -1, size.cx, size.cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	}

	return size;
}

void CKofMFCMenuButton::OnDraw(CDC* pDC, const CRect& rect, UINT uiState)
{
	ASSERT_VALID(pDC);

	CSize sizeArrow = CMenuImages::Size();

	CRect rectParent = rect;
	rectParent.right -= sizeArrow.cx + nImageHorzMargin;

	CKofMFCButton::OnDraw(pDC, rectParent, uiState);

	CRect rectArrow = rect;
	rectArrow.left = rectParent.right;

	CMenuImages::Draw(pDC, m_bRightArrow ? CMenuImages::IdArrowRightLarge : CMenuImages::IdArrowDownLarge,
		rectArrow, (uiState & ODS_DISABLED) ? CMenuImages::ImageGray : CMenuImages::ImageBlack);

	if (m_bDefaultClick)
	{
		//----------------
		// Draw separator:
		//----------------
		CRect rectSeparator = rectArrow;
		rectSeparator.right = rectSeparator.left + 2;
		rectSeparator.DeflateRect(0, 2);

		if (!m_bWinXPTheme || m_bDontUseWinXPTheme)
		{
			rectSeparator.left += m_sizePushOffset.cx;
			rectSeparator.top += m_sizePushOffset.cy;
		}

		pDC->Draw3dRect(rectSeparator, afxGlobalData.clrBtnDkShadow, afxGlobalData.clrBtnHilite);
	}
}

void CKofMFCMenuButton::OnShowMenu()
{
	if (m_hMenu == NULL || m_bMenuIsActive)
	{
		return;
	}

	CRect rectWindow;
	GetWindowRect(rectWindow);

	int x, y;

	if (m_bRightArrow)
	{
		x = rectWindow.right;
		y = rectWindow.top;
	}
	else
	{
		x = rectWindow.left;
		y = rectWindow.bottom;
	}

	if (m_bStayPressed)
	{
		m_bPushed = TRUE;
		m_bHighlighted = TRUE;
	}

	m_bMenuIsActive = TRUE;
	Invalidate();

	if (!m_bOSMenu && ((CWinAppEx*)AfxGetApp())->GetContextMenuManager() != NULL)
	{
		m_nMenuResult = ((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->TrackPopupMenu(m_hMenu, x, y, this);
		SetFocus();
	}
	else
	{
		m_nMenuResult = ::TrackPopupMenu(m_hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_NONOTIFY | TPM_RETURNCMD, x, y, 0, GetSafeHwnd(), NULL);
	}

	if (m_nMenuResult != 0)
	{
		//-------------------------------------------------------
		// Trigger mouse up event(to button click notification):
		//-------------------------------------------------------
		CWnd* pParent = GetParent();
		if (pParent != NULL)
		{
			pParent->SendMessage( WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM) m_hWnd);
		}
	}

	m_bPushed = FALSE;
	m_bHighlighted = FALSE;
	m_bMenuIsActive = FALSE;

	Invalidate();
	UpdateWindow();

	if (m_bCaptured)
	{
		ReleaseCapture();
		m_bCaptured = FALSE;
	}
}

void CKofMFCMenuButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_SPACE || nChar == VK_DOWN)
	{
		m_bClickOnMenu = TRUE;
		OnShowMenu();
		return;
	}

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKofMFCMenuButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bMenuIsActive)
	{
		Default();
		return;
	}

	m_bClickOnMenu = TRUE;

	if (m_bDefaultClick)
	{
		CRect rectClient;
		GetClientRect(rectClient);

		CRect rectArrow = rectClient;
		rectArrow.left = rectArrow.right - CMenuImages::Size().cx - nImageHorzMargin;

		if (!rectArrow.PtInRect(point))
		{
			m_bClickOnMenu = FALSE;
			m_nMenuResult = 0;
			CKofMFCButton::OnLButtonDown(nFlags, point);
			return;
		}
	}

	SetFocus();
	OnShowMenu();
}

UINT CKofMFCMenuButton::OnGetDlgCode()
{
	return DLGC_WANTARROWS;
}

void CKofMFCMenuButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bStayPressed && m_bMenuIsActive && m_bPushed)
	{
		m_bClickiedInside = FALSE;

		CButton::OnLButtonUp(nFlags, point);

		if (m_bCaptured)
		{
			ReleaseCapture();
			m_bCaptured = FALSE;
		}
	}
	else if (!m_bClickOnMenu)
	{
		CKofMFCButton::OnLButtonUp(nFlags, point);
	}
}

void CKofMFCMenuButton::OnKillFocus(CWnd* pNewWnd)
{
	if (m_bStayPressed && m_bMenuIsActive && m_bPushed)
	{
		CButton::OnKillFocus(pNewWnd);

		if (m_bCaptured)
		{
			ReleaseCapture();
			m_bCaptured = FALSE;
		}

		m_bClickiedInside = FALSE;
		m_bHover = FALSE;
	}
	else
	{
		CKofMFCButton::OnKillFocus(pNewWnd);
	}
}

BOOL CKofMFCMenuButton::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN &&
		pMsg->wParam == VK_RETURN &&
		CMFCPopupMenu::GetActiveMenu() == NULL)
	{
		m_bClickOnMenu = TRUE;
		OnShowMenu();
		return TRUE;
	}

	return CKofMFCButton::PreTranslateMessage(pMsg);
}

void CKofMFCMenuButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_bMenuIsActive)
	{
		CKofMFCButton::OnLButtonDblClk(nFlags, point);
		m_bClickOnMenu = FALSE;
	}
	if (m_bCaptured)
	{
		ReleaseCapture ();
		m_bCaptured = FALSE;
	}
}