// ..\src\KofMFCFontComboBox.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofMFCFontComboBox.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCFontComboBox

CKofMFCFontComboBox::CKofMFCFontComboBox()
{
	m_bIsDroppedDown = FALSE;
	m_bIsButtonHighlighted = FALSE;
	m_rectBtn.SetRectEmpty();
	m_bTracked = FALSE;
}

CKofMFCFontComboBox::~CKofMFCFontComboBox()
{
}

BEGIN_MESSAGE_MAP(CKofMFCFontComboBox, CMFCFontComboBox)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	ON_CONTROL_REFLECT_EX(CBN_CLOSEUP, &CKofMFCFontComboBox::OnCbnCloseup)
	ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, &CKofMFCFontComboBox::OnCbnDropdown)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CKofMFCFontComboBox::OnPaint()
{
	if ((GetStyle () & 0x0003L) == CBS_SIMPLE)
	{
		Default ();
		return;
	}

	if (!TRUE && !FALSE)
	{
		Default ();
		return;
	}

	CPaintDC dc(this); // device context for painting

	BYTE alpha = 0;
	if (FALSE)
	{
		alpha = 255;
	}

	CMemDC memDC (dc, this);
	CDC* pDC = &memDC.GetDC ();

	CRect rectClient;
	GetClientRect (rectClient);

	CDrawingManager dm (*pDC);
	dm.DrawRect (rectClient, afxGlobalData.clrWindow, (COLORREF)-1);

	SendMessage (WM_PRINTCLIENT, (WPARAM) pDC->GetSafeHdc (), (LPARAM) PRF_CLIENT);

	const int cxDropDown = ::GetSystemMetrics (SM_CXVSCROLL) + 4;

	m_rectBtn = rectClient;
	m_rectBtn.left = m_rectBtn.right - cxDropDown;
	m_rectBtn.DeflateRect (1, 1);

	dm.DrawRect (rectClient, (COLORREF)-1, afxGlobalData.clrBarShadow);
	CKofStyleHelper::GetInstance()->OnDrawEditBorder(pDC, rectClient, m_bIsButtonHighlighted, m_bIsDroppedDown, IsWindowEnabled());
	rectClient.DeflateRect (1, 1);
	dm.DrawRect (rectClient, (COLORREF)-1, afxGlobalData.clrWindow);
	rectClient.DeflateRect (1, 1);
	dm.DrawRect (rectClient, (COLORREF)-1, afxGlobalData.clrWindow);

	CKofStyleHelper::GetInstance()->OnDrawRibbonComboDropButton(pDC, m_rectBtn, !IsWindowEnabled(), m_bIsDroppedDown, m_bIsButtonHighlighted);
}

void CKofMFCFontComboBox::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) == 0)
	{
		BOOL bIsButtonHighlighted = m_bIsButtonHighlighted;
		m_bIsButtonHighlighted = m_rectBtn.PtInRect (point);

		if (bIsButtonHighlighted != m_bIsButtonHighlighted)
		{
			if (!m_bTracked)
			{
				if (m_bIsButtonHighlighted)
				{
					SetCapture ();
					m_bTracked = TRUE;
				}
			}
			else
			{
				if (!m_bIsButtonHighlighted)
				{
					ReleaseCapture ();
					m_bTracked = FALSE;
				}
			}

			RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);
		}
	}

	CComboBox::OnMouseMove(nFlags, point);
}

void CKofMFCFontComboBox::OnCancelMode()
{
	CComboBox::OnCancelMode();

	if (m_bTracked)
	{
		ReleaseCapture ();
		m_bIsButtonHighlighted = FALSE;
		m_bTracked = FALSE;

		RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);
	}
}

void CKofMFCFontComboBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bTracked)
	{
		ReleaseCapture ();
		m_bIsButtonHighlighted = FALSE;
		m_bTracked = FALSE;

		RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);
	}

	CComboBox::OnLButtonDown(nFlags, point);
}

BOOL CKofMFCFontComboBox::OnCbnCloseup()
{
	m_bIsDroppedDown = FALSE;
	m_bIsButtonHighlighted = FALSE;

	RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);

	return FALSE;
}

BOOL CKofMFCFontComboBox::OnCbnDropdown()
{
	if (m_bTracked)
	{
		ReleaseCapture ();
		m_bTracked = FALSE;
	}

	m_bIsDroppedDown = TRUE;
	m_bIsButtonHighlighted = FALSE;
	RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);

	return FALSE;
}
HBRUSH CKofMFCFontComboBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (NULL == m_edit.GetSafeHwnd())
		{
			m_edit.SubclassWindow(pWnd->GetSafeHwnd());
			m_edit.SetNeedBorder(FALSE);
		}
	} 
	else
	{
	}
	HBRUSH hbr = CMFCFontComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

void CKofMFCFontComboBox::OnDestroy()
{
	if (m_edit.GetSafeHwnd())
	{
		m_edit.UnsubclassWindow();
	}
	CMFCFontComboBox::OnDestroy();
}
