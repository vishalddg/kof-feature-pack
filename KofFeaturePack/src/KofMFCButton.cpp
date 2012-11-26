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

}

CKofMFCButton::~CKofMFCButton()
{
}


BEGIN_MESSAGE_MAP(CKofMFCButton, CMFCButton)
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
