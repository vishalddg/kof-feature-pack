// ..\src\KofComboBox.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofComboBox.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofComboBox

IMPLEMENT_DYNAMIC(CKofComboBox, CComboBox)

CKofComboBox::CKofComboBox()
{
	m_bIsDroppedDown = FALSE;
	m_bIsButtonHighlighted = FALSE;
	m_rectBtn.SetRectEmpty();
	m_bTracked = FALSE;
}

CKofComboBox::~CKofComboBox()
{
}

BEGIN_MESSAGE_MAP(CKofComboBox, CComboBox)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDOWN()
	ON_CONTROL_REFLECT_EX(CBN_CLOSEUP, &CKofComboBox::OnCbnCloseup)
	ON_CONTROL_REFLECT_EX(CBN_DROPDOWN, &CKofComboBox::OnCbnDropdown)
END_MESSAGE_MAP()

void CKofComboBox::OnPaint()
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

	CKofStyleHelper::GetInstance()->OnDrawRibbonComboDropButton(pDC, m_rectBtn, !IsWindowEnabled(), m_bIsDroppedDown, m_bIsButtonHighlighted);
}

void CKofComboBox::OnMouseMove(UINT nFlags, CPoint point)
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

void CKofComboBox::OnCancelMode()
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

void CKofComboBox::OnLButtonDown(UINT nFlags, CPoint point)
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

BOOL CKofComboBox::OnCbnCloseup()
{
	m_bIsDroppedDown = FALSE;
	m_bIsButtonHighlighted = FALSE;

	RedrawWindow (NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_UPDATENOW | RDW_ALLCHILDREN);

	return FALSE;
}

BOOL CKofComboBox::OnCbnDropdown()
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
