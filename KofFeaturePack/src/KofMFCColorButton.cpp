// ..\src\KofMFCColorButton.cpp : 实现文件

#include "stdafx.h"
#include "..\include\KofMFCColorButton.h"
#include "..\include\KofStyleHelper.h"

//////////////////////////////////////////////////////////////////////////
// CKofMFCColorButton

IMPLEMENT_DYNAMIC(CKofMFCColorButton, CMFCColorButton)

CKofMFCColorButton::CKofMFCColorButton()
{

}

CKofMFCColorButton::~CKofMFCColorButton()
{
}

BEGIN_MESSAGE_MAP(CKofMFCColorButton, CMFCColorButton)
END_MESSAGE_MAP()

void CKofMFCColorButton::OnDraw( CDC* pDC, const CRect& rect, UINT uiState )
{
	ASSERT_VALID(pDC);

	if (m_pPalette == NULL)
	{
		RebuildPalette(NULL);
	}

	CPalette* pCurPalette = pDC->SelectPalette(m_pPalette, FALSE);
	pDC->RealizePalette();

	CSize sizeArrow = CMenuImages::Size();

	CRect rectColor = rect;
	rectColor.right -= sizeArrow.cx + 8;

	CRect rectArrow = rect;
	rectArrow.left = rectColor.right;

	COLORREF color = m_Color;
	if (color == (COLORREF) -1) // Automatic
	{
		//---------------------------
		// Draw automatic text label:
		//---------------------------
		color = m_ColorAutomatic;

		if (!m_strAutoColorText.IsEmpty())
		{
			rectColor.right = rectColor.left + rectColor.Height();

			CRect rectText = rect;
			rectText.left = rectColor.right;
			rectText.right = rectArrow.left;

			CFont* pOldFont = SelectFont(pDC);
			ENSURE(pOldFont != NULL);

			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(afxGlobalData.clrBtnText);
			pDC->DrawText(m_strAutoColorText, rectText, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);

			pDC->SelectObject(pOldFont);
		}
	}

	//----------------
	// Draw color box:
	//----------------
	rectColor.DeflateRect(2, 2);
	pDC->Draw3dRect(rectColor, afxGlobalData.clrBtnHilite, afxGlobalData.clrBtnHilite);
	rectColor.DeflateRect(1, 1);
	pDC->Draw3dRect(rectColor, afxGlobalData.clrBtnDkShadow, afxGlobalData.clrBtnDkShadow);
	rectColor.DeflateRect(1, 1);

	if (color != (COLORREF)-1 &&(uiState & ODS_DISABLED) == 0)
	{
		if (afxGlobalData.m_nBitsPerPixel == 8) // 256 colors
		{
			ASSERT_VALID(m_pPalette);
			color =  PALETTEINDEX(m_pPalette->GetNearestPaletteIndex(color));
		}

		CBrush br(color);
		pDC->FillRect(rectColor, &br);
	}

	//----------------------
	// Draw drop-down arrow:
	//----------------------
	CRect rectArrowWinXP = rectArrow;
	rectArrowWinXP.DeflateRect(1, 1);
	CKofStyleHelper::GetInstance()->OnDrawRibbonComboDropButton(pDC, rectArrowWinXP, (uiState & ODS_DISABLED), m_pPopup != NULL, m_bHighlighted);

	if (pCurPalette != NULL)
	{
		pDC->SelectPalette(pCurPalette, FALSE);
	}
}

void CKofMFCColorButton::OnDrawBorder( CDC* pDC, CRect& rectClient, UINT uiState )
{
	ASSERT_VALID(pDC);
	ASSERT(m_nFlatStyle != BUTTONSTYLE_NOBORDERS); // Always has borders

	CKofStyleHelper::GetInstance()->OnDrawEditBorder(pDC, rectClient, m_bHighlighted, m_pPopup != NULL, IsWindowEnabled());
}

void CKofMFCColorButton::SetColors( const CArray<COLORREF, COLORREF>& colors )
{
	if (m_Colors.GetSize() != 0)
	{
		m_Colors.SetSize(0);
		m_Colors.FreeExtra();
	}

	m_Colors.Append(colors);
}
