#include "StdAfx.h"
#include "..\include\KofStyleHelper.h"

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
}

CKofStyleHelper::~CKofStyleHelper(void)
{
	m_clrDlgBackground = (COLORREF)-1;
	m_brDlgBackground.DeleteObject();
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
			switch (style2007)
			{
			case CMFCVisualManagerOffice2007::Office2007_LunaBlue:
				break;
			case CMFCVisualManagerOffice2007::Office2007_ObsidianBlack:
				break;
			case CMFCVisualManagerOffice2007::Office2007_Aqua:
				break;
			case CMFCVisualManagerOffice2007::Office2007_Silver:
				break;
			}			
		}
		break;
	default:
		{
			m_clrDlgBackground = afxGlobalData.clrBarFace;			
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
	return CSize (15, 15);
}

void CKofStyleHelper::OnDrawRadioButton( CDC *pDC, CRect rect, BOOL bOn, BOOL bHighlighted, BOOL bPressed, BOOL bEnabled )
{
}

BOOL CKofStyleHelper::OnDrawPushButton( CDC* pDC, CRect rect, CMFCButton* pButton, COLORREF& clrText )
{
	return FALSE;
}
