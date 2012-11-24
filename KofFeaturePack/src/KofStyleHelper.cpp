#include "StdAfx.h"
#include "..\include\KofStyleHelper.h"
#include "afxtagmanager.h"

class CKofMFCVisualManager : public CMFCVisualManager
{
	friend class CKofStyleHelper;
};

//////////////////////////////////////////////////////////////////////////
// CKofStyleHelper

CKofStyleHelper::CKofStyleHelper(void)
:m_Style(KOF_MAXCOUNT)
{
	m_clrDlgBackground = (COLORREF)-1;
	m_clrRibbonEditBorder = (COLORREF)-1;
	m_clrRibbonEditBorderDisabled = (COLORREF)-1;
	m_clrRibbonEditBorderHighlighted = (COLORREF)-1;
	m_clrRibbonEditBorderPressed = (COLORREF)-1;
}

CKofStyleHelper::~CKofStyleHelper(void)
{
	m_clrDlgBackground = (COLORREF)-1;
	m_brDlgBackground.DeleteObject();
	m_ctrlRibbonBtnPush.CleanUp();
}

BOOL CKofStyleHelper::SetStyle( UINT nStyle )
{
	if (nStyle >= KOF_MAXCOUNT)
	{
		return FALSE;
	}

	m_Style = nStyle;
	UINT style2007 = 4;
	if (KOF_CMFCVisualManagerOffice2007 == m_Style)
	{
		style2007 = CMFCVisualManagerOffice2007::GetStyle();
	}

	switch (m_Style)
	{
	case KOF_CMFCVisualManagerOffice2007:
		{
			m_clrDlgBackground = afxGlobalData.clrBarLight;
			m_ctrlRibbonBtnPush.CleanUp();

			CString strID = _T("BLUE_IDB_OFFICE2007_RIBBON_BUTTONS_PUSH");
			CMFCControlRendererInfo params(strID, CRect(0, 0, 0, 0), CRect(0, 0, 0, 0));

			CString strItem = _T("<SIZE>102, 22</SIZE><CORNERS>3, 4, 3, 3</CORNERS>");
			if (CTagManager::ParseControlRendererInfo(strItem, params))
			{
				//HINSTANCE hinstRes = AfxFindResourceHandle(strStyle, AFX_RT_STYLE_XML);
				m_ctrlRibbonBtnPush.Create(params);
			}
			switch (style2007)
			{
			case CMFCVisualManagerOffice2007::Office2007_LunaBlue:
				m_clrDlgBackground = RGB(213, 228, 242);
				m_clrRibbonEditBorder = RGB(171, 193, 222);
				m_clrRibbonEditBorderDisabled = RGB(177, 187, 198);
				m_clrRibbonEditBorderHighlighted = RGB(179, 199, 225);
				m_clrRibbonEditBorderPressed = RGB(179, 199, 225);
				break;
			case CMFCVisualManagerOffice2007::Office2007_ObsidianBlack:
				m_clrRibbonEditBorder = RGB(137, 137, 137);
				m_clrRibbonEditBorderDisabled = RGB(204, 204, 204);
				m_clrRibbonEditBorderHighlighted = RGB(137, 137, 137);
				m_clrRibbonEditBorderPressed = RGB(137, 137, 137);
				break;
			case CMFCVisualManagerOffice2007::Office2007_Aqua:
				m_clrRibbonEditBorder = RGB(177, 187, 198);
				m_clrRibbonEditBorderDisabled = RGB(177, 187, 198);
				m_clrRibbonEditBorderHighlighted = RGB(148, 168, 198);
				m_clrRibbonEditBorderPressed = RGB(148, 168, 198);
				break;
			case CMFCVisualManagerOffice2007::Office2007_Silver:
				m_clrRibbonEditBorder = RGB(169, 177, 184);
				m_clrRibbonEditBorderDisabled = RGB(177, 187, 198);
				m_clrRibbonEditBorderHighlighted = RGB(164, 164, 164);
				m_clrRibbonEditBorderPressed = RGB(164, 164, 164);
				break;
			}			
		}
		break;
	default:
		{
			m_clrDlgBackground = afxGlobalData.clrBarFace;
			m_clrRibbonEditBorder = afxGlobalData.clrBarShadow;
			m_clrRibbonEditBorderDisabled = m_clrRibbonEditBorder;
			m_clrRibbonEditBorderHighlighted = m_clrRibbonEditBorder;
			m_clrRibbonEditBorderPressed = m_clrRibbonEditBorder;
		}
	}
	m_brDlgBackground.DeleteObject();
	m_brDlgBackground.CreateSolidBrush(m_clrDlgBackground);
	return TRUE;
}

BOOL CKofStyleHelper::OnFillDialog( CDC* pDC, CWnd* pDlg, CRect rect )
{
	ASSERT_VALID (pDC);
	pDC->FillRect (rect, &GetDlgBackBrush(pDlg));

	return TRUE;
}

CBrush& CKofStyleHelper::GetDlgBackBrush( CWnd* pDlg )
{
	pDlg;
	return m_brDlgBackground;
}

CSize CKofStyleHelper::GetCheckRadioDefaultSize()
{
	// Õâ±ß¼ò»¯ÁË
	if (KOF_CMFCVisualManagerOffice2007 == m_Style)
	{
		return CSize (15, 15);
	}
	return CSize (::GetSystemMetrics (SM_CXMENUCHECK) + 1, ::GetSystemMetrics (SM_CYMENUCHECK) + 1);
}

void CKofStyleHelper::OnDrawRadioButton( CDC *pDC, CRect rect, BOOL bOn, BOOL bHighlighted, BOOL bPressed, BOOL bEnabled )
{
	switch (m_Style)
	{
	case KOF_CMFCVisualManagerWindows:
	case KOF_CMFCVisualManagerOffice2003:
	case KOF_CMFCVisualManagerVS2005:
	case KOF_CMFCVisualManagerOffice2007:
		if (CMFCVisualManager::GetInstance()->DrawRadioButton(pDC, rect, bHighlighted, bOn, bEnabled, bPressed))
		{
			return;
		}
		break;
	}
	CDrawingManager dm (*pDC);

	rect.DeflateRect (1, 1);

	dm.DrawEllipse (rect,
		bEnabled ? afxGlobalData.clrBarHilite : afxGlobalData.clrBarFace,
		bHighlighted && bEnabled ? afxGlobalData.clrBarDkShadow : afxGlobalData.clrBarShadow);

	if (bOn)
	{
		rect.DeflateRect (rect.Width () / 3, rect.Width () / 3);

		dm.DrawEllipse (rect,
			bHighlighted && bEnabled ? afxGlobalData.clrBarDkShadow : afxGlobalData.clrBarShadow,
			(COLORREF)-1);
	}
}

BOOL CKofStyleHelper::OnDrawPushButton( CDC* pDC, CRect rect, CMFCButton* pButton, COLORREF& clrText )
{
	ASSERT_VALID (pDC);
	ASSERT_VALID (pButton);

	int index = 0;

	BOOL bDisabled    = !pButton->IsWindowEnabled ();
	BOOL bFocused     = pButton->GetSafeHwnd () == ::GetFocus ();
	BOOL bDefault     = FALSE;// pButton->IsDefaultButton ();
	BOOL bPressed     = pButton->IsPressed ();
	BOOL bChecked     = pButton->IsChecked ();
	BOOL bHighlighted = pButton->IsHighlighted ();

	bHighlighted |= bFocused;

	if (bDisabled)
	{
		index = 6;
	}
	else
	{
		if (bChecked)
		{
			index = 3;
		}
		else
		{
			if (bDefault && !bHighlighted)
			{
				index = 5;
			}
		}

		if (bPressed)
		{
			if (bHighlighted)
			{
				index = 2;
			}
		}
		else if (bHighlighted)
		{
			index++;
		}
	}

	afxGlobalData.DrawParentBackground (pButton, pDC);
	m_ctrlRibbonBtnPush.Draw (pDC, rect, index);

	if (bDisabled)
	{
		clrText = RGB(141, 141, 141);//m_clrToolBarBtnTextDisabled;
	}
	else if (bHighlighted)
	{
		clrText = RGB(0, 21, 110);//m_clrToolBarBtnTextHighlighted;
	}

	return TRUE;
}

BOOL CKofStyleHelper::IsOwnerDrawDlgSeparator( CWnd* /*pCtrl*/ )
{
	if (KOF_CMFCVisualManagerOffice2007 == m_Style)
	{
		return TRUE;
	}
	return FALSE;
}

void CKofStyleHelper::OnDrawDlgSeparator( CDC* pDC, CWnd* pCtrl, CRect rect, BOOL bIsHorz )
{
	if (KOF_CMFCVisualManagerOffice2007 != m_Style)
	{
		return;
	}
	CPen pen1(PS_SOLID, 0, afxGlobalData.clrBarShadow);
	CPen pen2(PS_SOLID, 0, afxGlobalData.clrBarLight);

	CRect rect1(rect);
	CRect rect2;

	if (bIsHorz)
	{
		rect1.top += rect.Height() / 2 - 1;
		rect1.bottom = rect1.top;
		rect2 = rect1;
		rect2.OffsetRect(0, 1);
	}
	else
	{
		rect1.left += rect.Width() / 2 - 1;
		rect1.right = rect1.left;
		rect2 = rect1;
		rect2.OffsetRect(1, 0);
	}

	if (CMFCToolBarImages::m_bIsDrawOnGlass)
	{
		CDrawingManager dm(*pDC);

		LOGPEN logpen;

		pen1.GetLogPen(&logpen);
		dm.DrawLine(rect1.left, rect1.top, rect1.right, rect1.bottom, logpen.lopnColor);

		pen2.GetLogPen(&logpen);
		dm.DrawLine(rect2.left, rect2.top, rect2.right, rect2.bottom, logpen.lopnColor);
	}
	else
	{
		CPen* pOldPen = pDC->SelectObject(&pen1);
		pDC->MoveTo(rect1.TopLeft());
		pDC->LineTo(rect1.BottomRight());

		pDC->SelectObject(&pen2);
		pDC->MoveTo(rect2.TopLeft());
		pDC->LineTo(rect2.BottomRight());

		pDC->SelectObject(pOldPen);
	}
}

void CKofStyleHelper::OnDrawEditBorder( CDC* pDC, CRect rect, BOOL bHighlighted, BOOL bDroppedDowned, BOOL bEnabled )
{
	COLORREF colorBorder = m_clrRibbonEditBorder;

	if (!bEnabled)
	{
		colorBorder = m_clrRibbonEditBorderDisabled;
	}
	else if (bHighlighted || bDroppedDowned)
	{
		colorBorder = bDroppedDowned ? m_clrRibbonEditBorderPressed : m_clrRibbonEditBorderHighlighted;
	}

	pDC->Draw3dRect(rect, colorBorder, colorBorder);
}

class CKofMFCToolBarComboBoxButton : public CMFCToolBarComboBoxButton
{
	friend class CKofStyleHelper;
};

void CKofStyleHelper::OnDrawRibbonComboDropButton( CDC* pDC, CRect rect, BOOL bDisabled, BOOL bIsDropped, BOOL bIsHighlighted )
{
	CKofMFCToolBarComboBoxButton buttonDummy;
	buttonDummy.m_bIsRibbon = TRUE;
	CMFCVisualManager::GetInstance ()->OnDrawComboDropButton (
		pDC, rect, bDisabled, bIsDropped,
		bIsHighlighted,
		&buttonDummy);
}