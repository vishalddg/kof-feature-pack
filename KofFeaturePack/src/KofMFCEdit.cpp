// ..\src\KofMFCEdit.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofMFCEdit.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCEdit

//IMPLEMENT_DYNAMIC(CKofMFCEdit, CMFCEditBrowseCtrl)

CKofMFCEdit::CKofMFCEdit()
{
	m_bIsNeedBorder = TRUE;
}

CKofMFCEdit::~CKofMFCEdit()
{
}

BEGIN_MESSAGE_MAP(CKofMFCEdit, CMFCEditBrowseCtrl)
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

void CKofMFCEdit::OnNcPaint()
{
	const BOOL bHasScrollBars = ((GetStyle () & WS_VSCROLL) == WS_VSCROLL) || ((GetStyle () & WS_HSCROLL) == WS_HSCROLL);

	CWindowDC dc (this);
	CRect rectWindow;
	GetWindowRect (rectWindow);

	if (/*bHasScrollBars ||*/ (!TRUE && !FALSE))
	{
		CMFCEditBrowseCtrl::OnNcPaint ();
	}
	else
	{
		if (bHasScrollBars)
		{
			CMFCEditBrowseCtrl::OnNcPaint ();
		}
		CRect rectBorder = rectWindow;
		rectBorder.bottom -= rectBorder.top;
		rectBorder.right -= rectBorder.left;
		rectBorder.left = rectBorder.top = 0;
		if (m_bIsNeedBorder)
		{
			CKofStyleHelper::GetInstance()->OnDrawEditBorder(&dc, rectBorder, m_bIsButtonHighlighted, m_bIsButtonPressed, IsWindowEnabled());
			rectBorder.DeflateRect(1, 1);
			dc.Draw3dRect(rectBorder, afxGlobalData.clrWindow, afxGlobalData.clrWindow);
		}
	}

	if (GetStyle () & WS_BORDER)
	{
		CMFCVisualManager::GetInstance()->OnDrawControlBorder (this);
	}

	if (m_Mode == BrowseMode_None)
	{
		return;
	}

	m_rectBtn = rectWindow;
	m_rectBtn.left = m_rectBtn.right -  m_nBrowseButtonWidth;

	CRect rectClient;
	GetClientRect (rectClient);
	ClientToScreen (&rectClient);

	m_rectBtn.OffsetRect (rectClient.right + m_nBrowseButtonWidth - rectWindow.right, 0);
	m_rectBtn.top += rectClient.top - rectWindow.top;
	m_rectBtn.bottom -= rectWindow.bottom - rectClient.bottom;

	CRect rect = m_rectBtn;
	rect.OffsetRect (-rectWindow.left, -rectWindow.top);
	if (m_ImageBrowse.GetSafeHandle() != NULL)
	{
		rect.top -= 2;
		rect.bottom += 2;
		rect.right += 2;
		rect.left -= 1;
	}
	CRgn rgnClip;
	rgnClip.CreateRectRgnIndirect (&rect);

	dc.SelectClipRgn (&rgnClip);

	OnDrawBrowseButton (&dc, rect, m_bIsButtonPressed, m_bIsButtonHighlighted);

	dc.SelectClipRgn (NULL);

	ScreenToClient (&m_rectBtn);
}

HBRUSH CKofMFCEdit::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
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

void CKofMFCEdit::OnDrawBrowseButton( CDC* pDC, CRect rect, BOOL bIsButtonPressed, BOOL bHighlight )
{
	ASSERT(m_Mode != BrowseMode_None);
	ASSERT_VALID(pDC);

	CMFCVisualManager::AFX_BUTTON_STATE state = CMFCVisualManager::ButtonsIsRegular;

	if (bIsButtonPressed)
	{
		state = CMFCVisualManager::ButtonsIsPressed;
	}
	else if (bHighlight)
	{
		state = CMFCVisualManager::ButtonsIsHighlighted;
	}

	COLORREF clrText = afxGlobalData.clrBtnText;

	if (m_ImageBrowse.GetSafeHandle() != NULL)
	{
		rect.DeflateRect(1, 1);
		CKofStyleHelper::GetInstance()->OnDrawRibbonComboDropButton(pDC, rect, !IsWindowEnabled(), bIsButtonPressed, bHighlight);
	} 
	else
	{
		if (!CMFCVisualManager::GetInstance()->OnDrawBrowseButton(pDC, rect, this, state, clrText))
		{
			return;
		}
	}	

	int iImage = 0;

	if (m_ImageBrowse.GetSafeHandle() != NULL)
	{
		if (m_bDefaultImage)
		{
			switch (m_Mode)
			{
			case BrowseMode_Folder:
				iImage = 0;
				break;

			case BrowseMode_File:
				iImage = 1;
				break;
			}
		}

		CPoint ptImage;
		ptImage.x = rect.CenterPoint().x - m_sizeImage.cx / 2;
		ptImage.y = rect.CenterPoint().y - m_sizeImage.cy / 2;

		if (bIsButtonPressed && CMFCVisualManager::GetInstance()->IsOffsetPressedButton())
		{
			ptImage.x++;
			ptImage.y++;
		}

		m_ImageBrowse.Draw(pDC, iImage, ptImage, ILD_NORMAL);
	}
	else if (!m_strLabel.IsEmpty())
	{
		COLORREF clrTextOld = pDC->SetTextColor(clrText);
		int nTextMode = pDC->SetBkMode(TRANSPARENT);
		CFont* pFont = (CFont*) pDC->SelectStockObject(DEFAULT_GUI_FONT);

		CRect rectText = rect;
		rectText.DeflateRect(1, 2);
		rectText.OffsetRect(0, -2);

		if (bIsButtonPressed)
		{
			rectText.OffsetRect(1, 1);
		}

		pDC->DrawText(m_strLabel, rectText, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		pDC->SetTextColor(clrTextOld);
		pDC->SetBkMode(nTextMode);
		pDC->SelectObject(pFont);
	}
}

void CKofMFCEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CKofStyleHelper::GetInstance()->OnEditContextMenu(pWnd, point);
}
