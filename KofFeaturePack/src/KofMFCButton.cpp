// KofMFCButton.cpp : implementation file

#include "stdafx.h"
#include "..\include\KofMFCButton.h"
#include "..\include\KofStyleHelper.h"

static const COLORREF clrDefault = (COLORREF) -1;

//////////////////////////////////////////////////////////////////////////
// CKofMFCButton

IMPLEMENT_DYNCREATE(CKofMFCButton, CMFCButton)

CKofMFCButton::CKofMFCButton()
{
	m_bIsLeftText = FALSE;
	m_b3State = FALSE;
	m_bIndeterminate = FALSE;
	m_bDefaultButton = FALSE;
}

CKofMFCButton::~CKofMFCButton()
{
}


BEGIN_MESSAGE_MAP(CKofMFCButton, CMFCButton)
	ON_WM_LBUTTONUP()
	ON_MESSAGE(BM_GETCHECK, &CKofMFCButton::OnGetCheck)
	ON_MESSAGE(BM_SETCHECK, &CKofMFCButton::OnSetCheck)
	ON_WM_GETDLGCODE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CKofMFCButton::DoDrawItem( CDC* pDCPaint, CRect rectClient, UINT itemState )
{
	CMemDC memDC (*pDCPaint, this);
	CDC* pDC = &memDC.GetDC ();

	m_clrText = clrDefault;

	BOOL bDefaultDraw = TRUE;
	BOOL bDefaultCheckRadio = (m_bCheckButton || m_bRadioButton) && (GetStyle () & BS_PUSHLIKE) == 0;

	if (((TRUE && !FALSE) || bDefaultCheckRadio) && !m_bTransparent)
	{
		if (bDefaultCheckRadio)
		{
			afxGlobalData.DrawParentBackground (this, pDC);

			//----------------
			// Draw check box:
			//----------------
			CRect rectCheck = rectClient;
			const CSize sizeCheck = CKofStyleHelper::GetInstance()->GetCheckRadioDefaultSize();

			if (m_bIsLeftText)
			{
				rectCheck.left = rectCheck.right - sizeCheck.cx;
			}
			else
			{
				rectCheck.right = rectCheck.left + sizeCheck.cx;
			}

			BOOL bMultiLine = (GetStyle () & BS_MULTILINE) != 0;

			if (bMultiLine)
			{
				if ((GetStyle () & BS_VCENTER) == BS_VCENTER)
				{
					rectCheck.top = rectCheck.CenterPoint ().y - sizeCheck.cy / 2;
				}
				else if ((GetStyle () & BS_BOTTOM) == BS_BOTTOM)
				{
					rectCheck.top = rectCheck.bottom - sizeCheck.cy;
				}
				else if ((GetStyle () & BS_TOP) == BS_TOP)
				{
				}
				else
				{
					rectCheck.top = rectCheck.CenterPoint ().y - sizeCheck.cy / 2;
				}
			}
			else
			{
				rectCheck.top = rectCheck.CenterPoint ().y - sizeCheck.cy / 2;
			}

			rectCheck.bottom = rectCheck.top + sizeCheck.cy;

			const BOOL bIsHighlighted = IsHighlighted () && IsWindowEnabled ();

			if (m_bCheckButton)
			{
				int nCheck = IsChecked () ? 1 : 0;

				if (m_b3State && m_bIndeterminate)
				{
					nCheck = 2;
				}

				CMFCVisualManager::GetInstance()->OnDrawCheckBoxEx (pDC,
					rectCheck, nCheck,
					bIsHighlighted, IsPressed () && bIsHighlighted, IsWindowEnabled ());
			}
			else
			{
				CKofStyleHelper::GetInstance()->OnDrawRadioButton(pDC,
					rectCheck, IsChecked () || (IsPressed () && bIsHighlighted),
					bIsHighlighted, IsPressed () && bIsHighlighted, IsWindowEnabled ());
			}

			if (m_bIsLeftText)
			{
				rectClient.right = rectCheck.left;
				rectClient.left++;
			}
			else
			{
				rectClient.left = rectCheck.right + 1;
			}

			bDefaultDraw = FALSE;
		}
		else
		{
			if (CKofStyleHelper::GetInstance()->OnDrawPushButton (pDC, rectClient, this, m_clrText))
			{
				rectClient.DeflateRect (2, 2);
				bDefaultDraw = FALSE;
			}
		}
	}

	if (bDefaultDraw)
	{
		OnFillBackground (pDC, rectClient);
		OnDrawBorder (pDC, rectClient, itemState);
	}

	//---------------------
	// Draw button content:
	//---------------------
	OnDraw (pDC, rectClient, itemState);

	if ((itemState & ODS_FOCUS) && m_bDrawFocus)
	{
		OnDrawFocusRect (pDC, rectClient);
	}
}

void CKofMFCButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT (lpDIS != NULL);
	ASSERT (lpDIS->CtlType == ODT_BUTTON);

	CDC* pDCPaint = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDCPaint);

	DoDrawItem (pDCPaint, lpDIS->rcItem, lpDIS->itemState);
}

void CKofMFCButton::PreSubclassWindow()
{
	InitStyleEx(GetStyle());

	ModifyStyle(BS_DEFPUSHBUTTON, BS_OWNERDRAW);
	CButton::PreSubclassWindow();

	LRESULT lres = ::SendMessage (m_hWnd, BM_GETCHECK, 0, 0);

	m_bChecked = (BOOL) lres;

	if (m_b3State && lres == BST_INDETERMINATE)
	{
		m_bIndeterminate = TRUE;
	}
}

void CKofMFCButton::InitStyleEx( DWORD dwStyle )
{
	switch (dwStyle & 0x0F)
	{
	case BS_CHECKBOX:
		m_bCheckButton = TRUE;
		break;
	case BS_AUTOCHECKBOX:
		m_bCheckButton = m_bAutoCheck = TRUE;
		break;
	case BS_3STATE:
		m_bCheckButton = m_b3State = TRUE;
		break;
	case BS_AUTO3STATE:
		m_bCheckButton = m_bAutoCheck = m_b3State = TRUE;
		break;
	case BS_RADIOBUTTON:
		m_bRadioButton = TRUE;
		break;
	case BS_AUTORADIOBUTTON:
		m_bRadioButton = m_bAutoCheck = TRUE;
		break;
	case BS_DEFPUSHBUTTON:
		m_bDefaultButton = TRUE;
		break;
	}

	if (m_bCheckButton || m_bRadioButton)
	{
		if (dwStyle & BS_LEFTTEXT)
		{
			m_bIsLeftText = TRUE;
		}

		switch (dwStyle & BS_CENTER)
		{
		case BS_LEFT:
		default:
			m_nAlignStyle = CMFCButton::ALIGN_LEFT;
			break;
		case BS_RIGHT:
			m_nAlignStyle = CMFCButton::ALIGN_RIGHT;
			break;
		case BS_CENTER:
			m_nAlignStyle = CMFCButton::ALIGN_CENTER;
			break;
		}
	}

	if (!m_bWinXPThemeWasChecked)
	{
		if (!m_bWinXPTheme)
		{
			EnableWindowsTheming(AfxFindResourceHandle(MAKEINTRESOURCE(1), _T("24")) != NULL);
		}

		m_bWinXPThemeWasChecked = TRUE;
	}
}

BOOL CKofMFCButton::PreCreateWindow(CREATESTRUCT& cs)
{
	InitStyleEx(cs.style);

	cs.style |= BS_OWNERDRAW;
	cs.style &= ~BS_DEFPUSHBUTTON;

	return CButton::PreCreateWindow(cs);
}

void CKofMFCButton::OnDraw( CDC* pDC, const CRect& rect, UINT uiState )
{
	CRect rectText = rect;
	CRect rectImage = rect;

	CString strText;
	GetWindowText (strText);

	if (m_sizeImage.cx != 0)
	{
		if (!strText.IsEmpty ())
		{
			if (m_bTopImage)
			{
				rectImage.bottom = rectImage.top + m_sizeImage.cy + GetVertMargin ();
				rectText.top = rectImage.bottom;
				rectText.bottom -= GetVertMargin ();
			}
			else if (m_bRightImage)
			{
				rectText.right -= m_sizeImage.cx + GetImageHorzMargin () / 2;
				rectImage.left = rectText.right;
				rectImage.right -= GetImageHorzMargin () / 2;
			}
			else
			{
				rectText.left +=  m_sizeImage.cx + GetImageHorzMargin () / 2;
				rectImage.left += GetImageHorzMargin () / 2;
				rectImage.right = rectText.left;
			}
		}

		// Center image:
		rectImage.DeflateRect ((rectImage.Width () - m_sizeImage.cx) / 2,
			max (0, (rectImage.Height () - m_sizeImage.cy) / 2));
	}
	else
	{
		rectImage.SetRectEmpty ();
	}

	//-----------
	// Draw text:
	//-----------
	CFont* pOldFont = SelectFont (pDC);
	ASSERT(pOldFont != NULL);

	pDC->SetBkMode (TRANSPARENT);

	UINT uiDTFlags = DT_END_ELLIPSIS;
	BOOL bIsSingleLine = FALSE;

	BOOL bDefaultCheckRadio = (m_bCheckButton || m_bRadioButton) && (GetStyle () & BS_PUSHLIKE) == 0;
	BOOL bMultiLine = (GetStyle () & BS_MULTILINE) != 0;

	COLORREF clrTextDefault = (bDefaultCheckRadio && TRUE) ? afxGlobalData.clrBarText : afxGlobalData.clrBtnText;
	COLORREF clrText = m_clrRegular == clrDefault ? clrTextDefault : m_clrRegular;

	if (m_bHighlighted && m_clrHover != clrDefault)
	{
		clrText = m_clrHover;
	}

	if (bDefaultCheckRadio && !bMultiLine)
	{
		uiDTFlags |= DT_VCENTER | DT_SINGLELINE;
		bIsSingleLine = TRUE;
	}
	else
	{
		if (bMultiLine)
		{
			uiDTFlags |= DT_WORDBREAK;

			if (!bDefaultCheckRadio)
			{
				rectText.DeflateRect (GetVertMargin () / 2, GetVertMargin () / 2);
			}

			CRect rectCalc = rectText;
			pDC->DrawText (strText, rectCalc, DT_CALCRECT | DT_WORDBREAK);

			if ((GetStyle () & BS_VCENTER) == BS_VCENTER)
			{
				rectText.top = rectText.CenterPoint ().y - rectCalc.Height () / 2;
			}
			else if ((GetStyle () & BS_BOTTOM) == BS_BOTTOM)
			{
				rectText.top = rectText.bottom - rectCalc.Height ();
			}
			else if ((GetStyle () & BS_TOP) == BS_TOP)
			{
			}
			else
			{
				rectText.top = rectText.CenterPoint ().y - rectCalc.Height () / 2;
			}

			rectText.bottom = rectText.top + rectCalc.Height ();
		}
		else if (strText.Find (_T('\n')) < 0)
		{
			uiDTFlags |= DT_VCENTER | DT_SINGLELINE;
			bIsSingleLine = TRUE;
		}
		else
		{
			rectText.DeflateRect (0, GetVertMargin () / 2);
		}

		switch (m_nAlignStyle)
		{
		case ALIGN_LEFT:
			uiDTFlags |= DT_LEFT;

			if (!bDefaultCheckRadio)
			{
				rectText.left += GetImageHorzMargin () / 2;
			}

			break;

		case ALIGN_RIGHT:
			uiDTFlags |= DT_RIGHT;

			if (!bDefaultCheckRadio)
			{
				rectText.right -= GetImageHorzMargin () / 2;
			}

			break;

		case ALIGN_CENTER:
			uiDTFlags |= DT_CENTER;
			break;
		}
	}

	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		uiDTFlags |= DT_RTLREADING;
	}

	if ((uiState & ODS_DISABLED) && m_bGrayDisabled)
	{
		if (!FALSE)
		{
			pDC->SetTextColor (afxGlobalData.clrBtnHilite);

			CRect rectShft = rectText;
			rectShft.OffsetRect (1, 1);
			OnDrawText (pDC, rectShft, strText, uiDTFlags, uiState);
		}

		pDC->SetTextColor (CMFCVisualManager::GetInstance ()->GetToolbarDisabledTextColor ());
	}
	else
	{
		if (m_clrText == clrDefault)
		{
			pDC->SetTextColor (clrText);
		}
		else
		{
			pDC->SetTextColor (m_clrText);
		}
	}

	if (m_bDelayFullTextTooltipSet)
	{
		BOOL bIsFullText = pDC->GetTextExtent (strText).cx <= rectText.Width ();
		SetTooltip (bIsFullText || !bIsSingleLine ? NULL : (LPCTSTR) strText);
		m_bDelayFullTextTooltipSet = FALSE;
	}

	OnDrawText (pDC, rectText, strText, uiDTFlags, uiState);

	//------------
	// Draw image:
	//------------
	if (!rectImage.IsRectEmpty ())
	{
		if (m_nStdImageId != (CMenuImages::IMAGES_IDS) -1)
		{
			CMenuImages::IMAGES_IDS id = m_nStdImageId;

			if ((uiState & ODS_DISABLED) && m_bGrayDisabled &&
				m_nStdImageDisabledId != 0)
			{
				id = m_nStdImageDisabledId;
			}

			CMenuImages::Draw (pDC, id, rectImage.TopLeft (), m_StdImageState);
		}
		else
		{
			BOOL bIsDisabled = (uiState & ODS_DISABLED) && m_bGrayDisabled;

			CMFCToolBarImages& imageChecked = 
				(bIsDisabled && m_ImageCheckedDisabled.GetCount () != 0) ?
m_ImageCheckedDisabled :
			(m_bHighlighted && m_ImageCheckedHot.GetCount () != 0) ?
m_ImageCheckedHot : m_ImageChecked;

			CMFCToolBarImages& image = 
				(bIsDisabled && m_ImageDisabled.GetCount () != 0) ?
m_ImageDisabled :
			(m_bHighlighted && m_ImageHot.GetCount () != 0) ?
m_ImageHot : m_Image;

			if (m_bChecked && imageChecked.GetCount () != 0)
			{
				CAfxDrawState ds;

				imageChecked.PrepareDrawImage (ds);
				imageChecked.Draw (pDC, rectImage.left, rectImage.top, 0, FALSE, 
					bIsDisabled && m_ImageCheckedDisabled.GetCount () == 0);
				imageChecked.EndDrawImage (ds);
			}
			else if (image.GetCount () != 0)
			{
				CAfxDrawState ds;

				image.PrepareDrawImage (ds);
				image.Draw (pDC, rectImage.left, rectImage.top, 0, FALSE, 
					bIsDisabled && m_ImageDisabled.GetCount () == 0);
				image.EndDrawImage (ds);
			}
		}
	}

	pDC->SelectObject (pOldFont);
}

void CKofMFCButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	BOOL bClicked = m_bPushed && m_bClickiedInside && m_bHighlighted;

	m_bPushed = FALSE;
	m_bClickiedInside = FALSE;
	m_bHighlighted = FALSE;

	if (bClicked && m_bAutoCheck)
	{
		if (m_b3State)
		{
			if (m_bIndeterminate)
			{
				m_bIndeterminate = FALSE;
				m_bChecked = FALSE;
			}
			else if (m_bChecked)
			{
				m_bIndeterminate = TRUE;
			}
			else
			{
				m_bChecked = TRUE;
			}
		}
		else if (m_bCheckButton)
		{
			m_bChecked = !m_bChecked;
		}
		else if (m_bRadioButton && !m_bChecked)
		{
			m_bChecked = TRUE;
			UncheckRadioButtonsInGroup ();
		}
	}

	HWND hWnd = GetSafeHwnd();

	if (m_bWasDblClk)
	{
		m_bWasDblClk = FALSE;
		CWnd* pParent = GetParent ();
		if (pParent != NULL)
		{
			pParent->SendMessage (	WM_COMMAND,
				MAKEWPARAM (GetDlgCtrlID (), BN_CLICKED),
				(LPARAM) m_hWnd);
		}
	}

	if (!::IsWindow (hWnd))
	{
		// The button was destroyed after send message
		return;
	}

	RedrawWindow ();

	CButton::OnLButtonUp(nFlags, point);

	if (!::IsWindow (hWnd))
	{
		// The button was destroyed after the OnLButtonUp handler
		return;
	}

	if (m_bCaptured)
	{
		ReleaseCapture ();
		m_bCaptured = FALSE;
	}

	if (m_nAutoRepeatTimeDelay > 0)
	{
		KillTimer (1);
	}

	if (m_pToolTip->GetSafeHwnd () != NULL)
	{
		m_pToolTip->Pop ();

		CString str;
		m_pToolTip->GetText (str, this);
		m_pToolTip->UpdateTipText (str, this);
	}
}

void CKofMFCButton::GetTooltip( CString& strTooltip )
{
	strTooltip.Empty ();

	if (m_pToolTip->GetSafeHwnd () != NULL)
	{
		m_pToolTip->GetText (strTooltip, this);
	}
}

void CKofMFCButton::OnDrawFocusRect( CDC* pDC, const CRect& rectClient )
{
	ASSERT_VALID (pDC);

	BOOL bDefaultCheckRadio = (m_bCheckButton || m_bRadioButton) && (GetStyle () & BS_PUSHLIKE) == 0;
	BOOL bMultiLineCheckRadio = bDefaultCheckRadio && (GetStyle () & BS_MULTILINE) != 0;

	CRect rectFocus = rectClient;

	if (bDefaultCheckRadio)
	{
		CString strText;
		GetWindowText (strText);

		strText.Remove (_T('&'));

		CFont* pOldFont = SelectFont (pDC);
		ASSERT(pOldFont != NULL);

		if (bMultiLineCheckRadio)
		{
			CRect rectCalc = rectFocus;
			pDC->DrawText (strText, rectCalc, DT_CALCRECT | DT_WORDBREAK);

			if ((GetStyle () & BS_VCENTER) == BS_VCENTER)
			{
				rectFocus.top = rectFocus.CenterPoint ().y - rectCalc.Height () / 2;
			}
			else if ((GetStyle () & BS_BOTTOM) == BS_BOTTOM)
			{
				rectFocus.top = rectFocus.bottom - rectCalc.Height ();
			}
			else if ((GetStyle () & BS_TOP) == BS_TOP)
			{
			}
			else
			{
				rectFocus.top = rectFocus.CenterPoint ().y - rectCalc.Height () / 2;
			}

			rectFocus.right = rectFocus.left + rectCalc.Width ();
			rectFocus.left--;
			rectFocus.bottom = rectFocus.top + rectCalc.Height ();

			if ((GetStyle () & BS_BOTTOM) == 0)
			{
				rectFocus.bottom++;
			}
		}
		else
		{
			rectFocus.right = rectFocus.left + pDC->GetTextExtent (strText).cx;
			rectFocus.top = rectFocus.CenterPoint ().y - pDC->GetTextExtent (strText).cy / 2;
			rectFocus.bottom = rectFocus.top + pDC->GetTextExtent (strText).cy;
			rectFocus.InflateRect (1, 1);
		}

		rectFocus.top = max (rectFocus.top, rectClient.top);
		rectFocus.bottom = min (rectFocus.bottom, rectClient.bottom);

		if (FALSE)
		{
			CDrawingManager dm (*pDC);
			dm.DrawRect (rectFocus, (COLORREF)-1, afxGlobalData.clrBarDkShadow);
		}
		else
		{
			pDC->DrawFocusRect (rectFocus);
		}

		pDC->SelectObject (pOldFont);
		return;
	}


	rectFocus.DeflateRect (1, 1);

	if (FALSE)
	{
		CDrawingManager dm (*pDC);
		dm.DrawRect (rectFocus, (COLORREF)-1, afxGlobalData.clrBarDkShadow);
	}
	else
	{
		if (!m_bWinXPTheme || m_bDontUseWinXPTheme)
		{
			COLORREF clrBckgr = (m_clrFace == (COLORREF)-1) ? afxGlobalData.clrBtnFace : m_clrFace;

			rectFocus.DeflateRect (1, 1);
			pDC->Draw3dRect (rectFocus, clrBckgr, clrBckgr);
		}

		pDC->DrawFocusRect (rectFocus);
	}
}

LRESULT CKofMFCButton::OnGetCheck( WPARAM, LPARAM )
{
	if (m_b3State && m_bIndeterminate)
	{
		return BST_INDETERMINATE;
	}

	if (m_bCheckButton || m_bRadioButton)
	{
		return m_bChecked ? BST_CHECKED	: BST_UNCHECKED;
	}

	return 0;
}

LRESULT CKofMFCButton::OnSetCheck( WPARAM fCheck, LPARAM )
{
	if (m_b3State)
	{
		switch (fCheck)
		{
		case BST_UNCHECKED:
			m_bChecked = FALSE;
			m_bIndeterminate = FALSE;
			break;

		case BST_CHECKED:
			m_bChecked = TRUE;
			m_bIndeterminate = FALSE;
			break;

		case BST_INDETERMINATE:
			m_bChecked = TRUE;
			m_bIndeterminate = TRUE;
			break;
		}

		Invalidate();
		UpdateWindow();
		return 0;
	}

	ASSERT (fCheck != BST_INDETERMINATE);

	if ((m_bCheckButton || m_bRadioButton) && (!m_bChecked) != (fCheck == BST_UNCHECKED)) 
	{
		m_bChecked = fCheck != BST_UNCHECKED;

		if (m_bRadioButton)
		{
			UncheckRadioButtonsInGroup ();
		}

		Invalidate();
		UpdateWindow();
	}

	return 0;
}

UINT CKofMFCButton::OnGetDlgCode()
{
	UINT uRes = CButton::OnGetDlgCode();

	if (m_bRadioButton)
	{
		uRes |= DLGC_RADIOBUTTON;
	}

	return uRes;
}

void CKofMFCButton::OnPaint()
{
	const BOOL bIsRadio = m_bRadioButton && !m_bAutoCheck;

	if (!m_b3State && !bIsRadio)
	{
		Default ();
		return;
	}

	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect (&rectClient);

	DoDrawItem (&dc, rectClient, (CWnd::GetFocus () == this) ? ODS_FOCUS : 0);
}
